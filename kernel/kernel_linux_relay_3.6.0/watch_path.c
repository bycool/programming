#include "fds.h"

enum map_type {
	MAP_NONE       = 0,
	MAP_ROOT       = 1, /* map_path */
	MAP_PATH       = 2, /* map_path_sub_dir */
	MAP_FILE       = 3, /* map_path_sub_file */
	MAP_SUFFIX     = 4, /* map_path_sub_suffix */
	MAP_NOT_PATH   = 5, /* map_path_not_sub_dir */
	MAP_NOT_FILE   = 6, /* map_path_not_sub_file */
	MAP_NOT_SUFFIX = 7  /* map_path_not_sub_suffix */
};

static char* str_map_type[] = {
	"MAP_NONE",
	"MAP_PATH", "MAP_PATH_SUB", "MAP_FILE", "MAP_SUFFIX",
	"MAP_NOT_PATH", "MAP_NOT_FILE", "MAP_NOT_SUFFIX"
};

struct fds_string {
	char* str;
	int len;
};

#define EMPTY_STR {NULL, 0}

struct fds_watch_path {
	enum map_type type;

	int mapid;

	struct fds_string path;
	struct fds_string file;
	struct fds_string suffix;

	struct fds_watch_path* sibling;
	struct fds_watch_path* content;
};

static bool wpath_ready = false;

atomic_t update_watch_rules = ATOMIC_INIT(0);
atomic_t rulse_1_used_cnt = ATOMIC_INIT(0);
atomic_t rulse_2_used_cnt = ATOMIC_INIT(0);

static struct fds_watch_path watchpath_rule_1 = {MAP_NONE, 0, {"/", 1}, EMPTY_STR, EMPTY_STR, NULL, NULL};
static struct fds_watch_path watchpath_rule_2 = {MAP_NONE, 0, {"/", 1}, EMPTY_STR, EMPTY_STR, NULL, NULL};

static char* fds_string_dup_len(const char* buffer, int size) {
	char* rc = NULL;
	if (size != 0) {
		rc = (char*)kmalloc(size + 1, GFP_ATOMIC);
		if (rc == NULL) {
			fds_relay_notify_memfull();
			return NULL;
		}
		memcpy(rc, buffer, size);
		rc[size] = '\0';
	}
	return rc;	
}

























