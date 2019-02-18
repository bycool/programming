#include "fds.h"

enum map_type
{
	MAP_NONE       = 0,
	MAP_ROOT       = 1, /* MAP_ROOT */
	MAP_PATH       = 2, /* 只监视子目录MAP_PATH_SUB */
	MAP_FILE       = 3, /* 只监视指定文件 */
	MAP_SUFFIX     = 4, /* 只监视指定类型的文件 */
	MAP_NOT_PATH   = 5, /* 目录下所有文件都不监视 */
	MAP_NOT_FILE   = 6, /* 指定文件不予监视 */
	MAP_NOT_SUFFIX = 7  /* 目录下所有类型都不监视 */
};

static char* str_map_type[] =
{
	"MAP_NONE", "MAP_PATH", "MAP_PATH_SUB", "MAP_FILE", "MAP_SUFFIX",
	"MAP_NOT_PATH", "MAP_NOT_FILE", "MAP_NOT_SUFFIX"
};

struct fds_string
{
	char* str;
	int len;
};

#define EMPTY_STR {NULL, 0}

struct fds_watch_path
{
	enum map_type type;

	int mapid;

	struct fds_string path;
	struct fds_string file;
	struct fds_string suffix;

	struct fds_watch_path* sibling;
	struct fds_watch_path* content;
};


static bool wpath_ready = false;

#if 0
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 32))
static DEFINE_SPINLOCK(lock);
#else
static spinlock_t lock = SPIN_LOCK_UNLOCKED;
#endif
#endif

atomic_t watchpath_is_update = ATOMIC_INIT(0);
atomic_t watchpath_used = ATOMIC_INIT(0);
atomic_t watchpath_update_used = ATOMIC_INIT(0);

static struct fds_watch_path watch_path =
	{MAP_NONE, 0, {"/", 1}, EMPTY_STR, EMPTY_STR, NULL, NULL};

static struct fds_watch_path update_watch_path = 
	{MAP_NONE, 0, {"/", 1}, EMPTY_STR, EMPTY_STR, NULL, NULL};


static bool append_watch_path(
	enum map_type type, int mapid, char* path, char* file, char* suffix);

static char* fds_string_dup_len(const char* buffer, int size)
{
	char* rc = NULL;

	if (size != 0)
	{
		rc = (char*)kmalloc(size + 1, GFP_ATOMIC);
		if (rc == NULL)
		{
			fds_relay_notify_memfull();
			return NULL;
		}

		memcpy(rc, buffer, size);
		rc[size] = '\0';
	}

	return rc;
}

static char* fds_string_dup(const char* buffer)
{
	return fds_string_dup_len(buffer, buffer == NULL ? 0 : strlen(buffer));
}

static void fds_string_assign(struct fds_string* var, char* str)
{
	var->str = str;
	var->len = str == NULL ? 0 : strlen(str);
}

static int fds_string_cmp(const char* str1, const char* str2)
{
	if (str1 == NULL && str2 == NULL)
		return 0;

	if (str1 != NULL && str2 != NULL)
		return strcmp(str1, str2);

	return 1;
}

static void fds_string_free(struct fds_string* pstring)
{
	if (pstring->str != NULL && pstring->len != 0)
	{
		kfree(pstring->str);
		pstring->str = NULL;
		pstring->len = 0;
	}
}

static void wpath_cleanup(struct fds_watch_path* wpath)
{
	struct fds_watch_path* node = NULL;

#define FREE_WATCH_PATH(wpath) \
	do { \
		fds_string_free(&wpath->path); \
		fds_string_free(&wpath->file); \
		fds_string_free(&wpath->suffix); \
	} while (0)

	if (wpath == NULL)
		return;

	for (node = wpath; node != NULL; node = node->sibling)
	{
		FREE_WATCH_PATH(node);
		wpath_cleanup(node->content);
	}
#undef FREE_WATCH_PATH
}

void watch_path_cleanup()
{
	wpath_ready = false;

	wpath_cleanup(watch_path.content);
	watch_path.type = MAP_NONE;
	watch_path.sibling = NULL;
	watch_path.content = NULL;

	if(update_watch_path.content){
		wpath_cleanup(update_watch_path.content);	
		update_watch_path.type = MAP_NONE;
		update_watch_path.sibling = NULL;
		update_watch_path.content = NULL;
	}

}

static bool under_path(const char* fullpath, int fpath_len,
	const struct fds_string* ppath)
{
	if (fpath_len >= ppath->len)
	{
		if (memcmp(fullpath, ppath->str, ppath->len) == 0)
			return true;
	}

	return false;
}

static struct fds_watch_path* get_watch_path(const char* fullpath, int path_len, int* which_rule)
{
	struct fds_watch_path* rc = NULL;
	struct fds_watch_path* wparent = NULL;

    if(atomic_read(&watchpath_is_update) == 2 || atomic_read(&watchpath_is_update)== 0){
        wparent = &update_watch_path;
		*which_rule = 2;
		//printk("which_rule = 1\n");
		atomic_add(1, &watchpath_used);
    }else if(atomic_read(&watchpath_is_update) == 1){
        wparent = &watch_path;
		*which_rule = 1;
		//printk("which_rule = 2\n");
		atomic_add(1, &watchpath_update_used);
	}

	for (rc = wparent->content; rc != NULL; rc = rc->sibling)
	{
		if (under_path(fullpath, path_len, &rc->path))
			break;
	}

	return rc;
}

static bool filter_match_path(const char* fullpath, int path_len,
	const struct fds_watch_path* wpath)
{
	return under_path(fullpath, path_len,  &wpath->path);
}

static bool filter_match_file(const char* fullpath, int path_len,
	const struct fds_watch_path* wpath)
{
	if (!under_path(fullpath, path_len, &wpath->path))
		return false;

	if (wpath->file.str != NULL)
		return strcmp(fullpath + wpath->path.len, wpath->file.str) == 0;

	return false;
}

static bool filter_match_suffix(const char* fullpath, int path_len,
	const struct fds_watch_path* wpath)
{
	if (wpath->path.str && !under_path(fullpath, path_len, &wpath->path))
		return false;

	return strcmp(fullpath + path_len - wpath->suffix.len,
		wpath->suffix.str) == 0;
}

static bool watch_excluded(const struct fds_watch_path* wpath,
	const char* fullpath, int path_len)
{
	const struct fds_watch_path* node = NULL;

	for (node = wpath->content; node != NULL; node = node->sibling)
	{
		switch (node->type)
		{
		case MAP_NOT_PATH:
			if (filter_match_path(fullpath, path_len, node))
				return true;
			break;
		case MAP_NOT_FILE:
			if (filter_match_file(fullpath, path_len, node))
				return true;
			break;
		case MAP_NOT_SUFFIX:
			if (filter_match_suffix(fullpath, path_len, node))
				return true;
			break;
		case MAP_PATH:
			if (node->path.len < path_len && memcmp(
				node->path.str, fullpath, node->path.len) == 0)
			{
				return watch_excluded(node, fullpath, path_len);
			}
			break;
		default:
			break;
		}
	}

	return false;
}

static bool watch_included(const struct fds_watch_path* wpath,
	const char* fullpath, int path_len)
{
	const struct fds_watch_path* node = wpath->content;

	bool bres_path = true;
	bool bres_file = true;
	bool bres_suffix = true;

	bool is_dir = fullpath[path_len - 1] == '/';

	while (node != NULL)
	{
		switch (node->type)
		{
		case MAP_PATH:
			if (filter_match_path(fullpath, path_len, node))
			{
				bres_path = true;
				bres_file = true;
				bres_suffix = true;

				node = node->content;
				continue;
			}

			bres_path = false;
			break;
		case MAP_FILE:
			if (is_dir)
				break;

			if (!under_path(fullpath, path_len, &node->path))
				break;

			if (!strcmp(fullpath + node->path.len, node->file.str))
				return true;

			bres_file = false;
			break;
		case MAP_SUFFIX:
			if (is_dir)
				break;

			if (node->path.str != NULL
				&& !under_path(fullpath, path_len, &node->path))
				break;

			if (strcmp(fullpath + path_len - node->suffix.len,
				node->suffix.str) == 0)
				return true;

			bres_suffix = false;
			break;
		default:
			break;
		}

		node = node->sibling;
	}

	return bres_path && (bres_file && bres_suffix);
}

#define USED_RULE_CNT \
	if(which_rule == 1) \
		atomic_sub(1, &watchpath_update_used); \
	else \
		atomic_sub(1, &watchpath_used);

bool monitored(const char* fullpath, bool isdir, char* mapid_cnt, char* mapid)
{
	int which_rule = -1;
	int path_len = 0;
	struct fds_watch_path* wpath = NULL;
	struct fds_watch_path* rc = NULL;
	struct fds_watch_path* wparent = NULL;

	if (fullpath == NULL)
		return 0;

	path_len = strlen(fullpath);
	*mapid_cnt = cnt = 0;

	if(atomic_read(&watchpath_is_update) == 2 || atomic_read(&watchpath_is_update)== 0){
		wparent = &update_watch_path;
		which_rule = 2;
		atomic_add(1, &watchpath_used);
	}else if(atomic_read(&watchpath_is_update) == 1){
		wparent = &watch_path;
		which_rule = 1;
		atomic_add(1, &watchpath_update_used);
	}


	for(rc = wparent->content; rc != NULL; rc = rc->sibling){
		if (under_path(fullpath, path_len, &rc->path))
			wpath = rc
		else
			continue;

		if (watch_excluded(wpath, fullpath, path_len))
		{
			continue;
		}

		if (!watch_included(wpath, fullpath, path_len))
		{
			continue;
		}
		mapid[cnt] = wpath->mapid;
		cnt++;
		*mapid_cnt = cnt;
		
	}

	USED_RULE_CNT
	if (cnt > 0)
		return true;
	else
		return false;
}

static int depart(const char* buffer, char** path, char** file, char** suffix)
{
	const char* ptmp = buffer;
	const char* ptr = NULL;

	*path = *file = *suffix = NULL;

	ptr = strrchr(ptmp, '/');
	if (ptr != NULL)
	{
		ptmp = ++ptr;
		*path = fds_string_dup_len(buffer, ptr - buffer);
		if (*path == NULL)
			return -1;
	}

	ptr = strstr(ptmp, "*.");
	if (ptr != NULL)
	{
		*suffix = fds_string_dup(ptr + 1);
		if (*suffix == NULL)
			return -1;
	}
	else
	{
		*file = fds_string_dup(ptmp);
		if (ptmp != NULL && strlen(ptmp) != 0 && *file == NULL)
			return -1;
	}

	return 0;
}

static bool wpath_equal(const struct fds_watch_path* wpath, enum map_type type, int mapid,
	const char* path, const char* file, const char* suffix)
{
	if (wpath == NULL)
		return false;

	return type == wpath->type && wpath->mapid == mapid
		&& fds_string_cmp(path, wpath->path.str) == 0
		&& fds_string_cmp(file, wpath->file.str) == 0
		&& fds_string_cmp(suffix, wpath->suffix.str) == 0;
}

static bool wpath_parent(const struct fds_watch_path* wpath, enum map_type type, int mapid,
	const char* path, const char* file, const char* suffix)
{
	int path_len = 0;

	if (path == NULL)
		return true;

	path_len = strlen(path);

	if (wpath == NULL || path == NULL)
		return false;

	if (wpath->type != MAP_ROOT
		&& wpath->type != MAP_PATH
		&& wpath->type != MAP_NOT_PATH)
	{
		return false;
	}

	if (path_len < wpath->path.len)
		return false;

	return memcmp(path, wpath->path.str, wpath->path.len) == 0 && wpath->mapid == mapid
		&& (path_len > wpath->path.len || file || suffix);
}

static bool wpath_child(const struct fds_watch_path* wpath, enum map_type type, int mapid,
	const char* path, const char* file, const char* suffix)
{
	int path_len = strlen(path);

	if (type != MAP_ROOT && type != MAP_PATH && type != MAP_NOT_PATH)
		return false;

	return path_len <= wpath->path.len && wpath->mapid == mapid
		&& memcmp(path, wpath->path.str, path_len) == 0;
}

static struct fds_watch_path* fds_alloc_wpath(enum map_type type, int mapid,
	const char* path, const char* file, const char* suffix)
{
	struct fds_watch_path* rc = NULL;

	rc = (struct fds_watch_path*)kmalloc(sizeof(*rc), GFP_ATOMIC);
	if (rc == NULL)
	{
		fds_relay_notify_memfull();
		return NULL;
	}

	fds_string_assign(&rc->path, (char*)path);
	fds_string_assign(&rc->file, (char*)file);
	fds_string_assign(&rc->suffix, (char*)suffix);

	rc->mapid = mapid;
	rc->type = type;
	rc->sibling = NULL;
	rc->content = NULL;

	return rc;
}

static bool append_watch_path(
	enum map_type type, int mapid, char* path, char* file, char* suffix)
{
	struct fds_watch_path* new_node = NULL;
	struct fds_watch_path* node = NULL;
	struct fds_watch_path* prev_sibling = NULL;
	struct fds_watch_path* wparent = NULL;
	struct fds_watch_path* wtemp = NULL;

	if (type == MAP_NONE)
		return false;

	new_node = fds_alloc_wpath(type, mapid, path, file, suffix);
	if (new_node == NULL)
		return false;

	if(atomic_read(&watchpath_is_update) == 2 || atomic_read(&watchpath_is_update)== 0)
		wparent = &watch_path;
	else if(atomic_read(&watchpath_is_update) == 1)
		wparent = &update_watch_path;

	node = wparent->content;
	while (node != NULL)
	{
		if (wpath_equal(node, type, mapid, path, file, suffix))
		{
			wpath_cleanup(new_node);
			return true;
		}

		if (wpath_parent(node, type, mapid, path, file, suffix))
		{
			wparent = node;
			prev_sibling = NULL;
			node = wparent->content;

			if (path == NULL)
				break;

			continue;
		}

		if (wpath_child(node, type, mapid, path, file, suffix))
		{
			wtemp = node->sibling;

			if (prev_sibling == NULL)
				wparent->content = wparent->content->sibling;
			else
				prev_sibling->sibling = node->sibling;

			node->sibling = new_node->content;
			new_node->content = node;

			node = wtemp;
			continue;
		}

		prev_sibling = node;
		node = node->sibling;
	}

	new_node->sibling = wparent->content;
	wparent->content = new_node;

	return true;
}

static void display_wpath(const struct fds_watch_path* wpath, int grade)
{
	if (wpath == NULL)
		return;

	switch (wpath->type)
	{
	case MAP_ROOT:
		printk("[%.2d][%-14.14s]%*s----[%s]\n", wpath->mapid,
			str_map_type[wpath->type], 2 * grade, "",
			wpath->path.str);
		break;
	case MAP_PATH:
	case MAP_NOT_PATH:
		printk("[%.2d][%-14.14s]%*s|----[%s]\n", wpath->mapid,
			str_map_type[wpath->type], 2 * grade, "",
			wpath->path.str);
		break;
	case MAP_FILE:
	case MAP_NOT_FILE:
		printk("[%.2d][%-14.14s]%*s|----[%s][%s]\n", wpath->mapid,
			str_map_type[wpath->type], 2 * grade, "",
			wpath->path.str, wpath->file.str);
		break;
	case MAP_SUFFIX:
	case MAP_NOT_SUFFIX:
		printk("[%.2d][%-14.14s]%*s|----[%s][%s]\n", wpath->mapid,
			str_map_type[wpath->type], 2 * grade, "",
			wpath->path.str, wpath->suffix.str);
		break;
	default:
		break;
	}
}

void display_watch_path(const struct fds_watch_path* wpath, int grade)
{
	const struct fds_watch_path* node = NULL;

	if (wpath == NULL)
		return;

	for (node = wpath; node != NULL; node = node->sibling)
	{
		display_wpath(node, grade);

		if (node->type == MAP_ROOT
			|| node->type == MAP_PATH
			|| node->type == MAP_NOT_PATH)
		{
			display_watch_path(node->content, grade + 1);
		}
	}
}
//size:len(mtype|sub_type|str'\0'|)
int append_watch_paths(const char __user* buffer, size_t size)
{
	int rc = -1;
	int mapid = 0;
	enum map_type mtype = MAP_NONE;
	int sub_type = buffer[1] & 0xFF;

	char args[1024] = {0};
	int args_size = size - 2;
	char* path = NULL;
	char* file = NULL;
	char* suffix = NULL;

	mapid = buffer[2];	

#define FREE_NONULL_PTR(ptr)  do { if (ptr != NULL) kfree(ptr); } while (0)

	snprintf(args, sizeof args, "%s", buffer + 3);
	fullpath_kis(args, &args_size);

	rc = depart(args, &path, &file, &suffix);
	if (rc != 0)
	{
		FREE_NONULL_PTR(path);
		FREE_NONULL_PTR(file);
		FREE_NONULL_PTR(suffix);

		printk("Failed to analyse path string [%s]\n", args);

		return -1;
	}

	switch (buffer[0] & 0xFF)
	{
	case MONITOR_PATHS:
		mtype = MAP_ROOT;
		break;
	case MONITOR_MAP_SUB:
		if (sub_type == FDS_MAP_PATH_SUB)
			mtype = MAP_PATH;
		else if (sub_type == FDS_MAP_FILE)
			mtype = suffix ? MAP_SUFFIX : MAP_FILE;

		break;
	case MONITOR_MAP_NOT:
		if (sub_type == FDS_MAP_NOT_PATH)
			mtype = MAP_NOT_PATH;
		else if (sub_type == FDS_MAP_NOT_FILE)
			mtype = suffix ? MAP_NOT_SUFFIX : MAP_NOT_FILE;

		break;
	case MONITOR_MAP_END:
		printk("---------------------------------------\n");
    	if(atomic_read(&watchpath_is_update) == 2 || atomic_read(&watchpath_is_update)== 0){
			atomic_set(&watchpath_is_update, 1);
			while(atomic_read(&watchpath_update_used)!=0){
				printk("update: %d\n", atomic_read(&watchpath_update_used));
				msleep(5);
			}
			display_watch_path(watch_path.content, 0);
			wpath_cleanup(update_watch_path.content);
			update_watch_path.type = MAP_NONE;
			update_watch_path.sibling = NULL;
			update_watch_path.content = NULL;
    	}else if(atomic_read(&watchpath_is_update) == 1){
			atomic_set(&watchpath_is_update, 2);
			while(atomic_read(&watchpath_used)!=0){
				printk("unupdate: %d\n", atomic_read(&watchpath_used));
				msleep(5);
			}
			display_watch_path(update_watch_path.content, 0);
			wpath_cleanup(watch_path.content);
		    watch_path.type = MAP_NONE;
		    watch_path.sibling = NULL;
		    watch_path.content = NULL;
		}
		printk("---------------------------------------\n");
		
		wpath_ready = true;
		return 0;
	default:
		break;
	}


	if (!append_watch_path(mtype, mapid, path, file, suffix))
	{
		FREE_NONULL_PTR(path);
		FREE_NONULL_PTR(file);
		FREE_NONULL_PTR(suffix);

		printk("append_watch_path error!\n");
		return -1;
	}

#undef FREE_NONULL_PTR

	return 0;
}

bool watch_path_ready()
{
	return wpath_ready;
}

