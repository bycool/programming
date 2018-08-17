#include "sync.h"

#define WATCH_START       '0'
#define WATCH_ROOT        '1'
#define WATCH_PATH        '2'
#define WATCH_FILE        '3'
#define WATCH_SUFFIX      '4'
#define WATCH_NOT_PATH    '5'
#define WATCH_NOT_FILE    '6'
#define WATCH_NOT_SUFFIX  '7'
#define WATCH_FINISH      '8'

static bool wpath_ready = false;

static DEFINE_SPINLOCK(lock);

enum wp_type {
    WP_START = 0,
    WP_ROOT = 1,      //监控目录
    WP_PATH = 2,      //只监控目录下子目录
    WP_FILE = 3,      //只监控目录下的文件
    WP_SUFFIX = 4,    //只监控目录下的某个后缀文件
    WP_NOT_PATH = 5,  //不监控某个子目录
    WP_NOT_FILE = 6,  //不监控的某个文件
    WP_NOT_SUFFIX = 7,//不监控某个后缀文件
    WP_FINISH = 8
};

static char* wptype[] = {
    "WP_START", "WP_ROOT", "WP_PATH", "WP_FILE",
    "WP_SUFFIX", "WP_NOT_PATH", "WP_NOT_FILE", "WP_NOT_SUFFIX",
    "WP_FINISH"
};

struct wpstr {
    char *str;
    int len;
};

struct wpnode {
	enum wp_type type;

	struct wpstr content;

    struct wpnode next;
}

struct wproot {
    enum wp_type type;

	long root_id;

    struct wpstr wp_root;

	struct wpnode* path;
	struct wpnode* file;
	struct wpnode* suffix;
	struct wpnode* notputh;
	struct wpnode* notfile;
	struct wpnode* notsuffix;

    struct wproot* brother;
};

static wpnode watchpath = {WP_STRAT, {"/",1}, NULL, NULL};



bool watchpath_ready(){
	return wpath_ready;
}

static char* wp_path_dup_str(const char* buffer, int size){
    char* rc = NULL;

    if(size != 0){
        rc = (char*)kmalloc(size+1, GFP_ATOMIC);
        if(rc == NULL){
			printf("kmalloc new str fail\n");
            return NULL;
        }

		memcpy(rc, buffer, size);
        rc[size] = '\0';
	}

    return rc;
}

static int wp_path_analysis(const char* buffer, char** content){
	const char* ptmp = buffer;
    const char* ptr = NULL;

    *content = NULL;

    ptr = strrchr(ptmp, '/');
    if(ptr != NULL){
		ptmp = ++ptr;
        *content = wp_path_dup_str(buffer, ptr-buffer);
        if(*content == NULL)
            return -1;
    }

    ptr = strstr(ptmp, "*.");
    if(ptr != NULL){
		*content = wp_path_dup_str(buffer, strlen(ptr));
		if(*content == NULL)
			return -1;
    }else{
        *content = wp_path_dup_str(buffer, strlen(ptmp));
		if(ptmp != NULL && strlen(ptmp) != 0 && *content == NULL)
			return -1;
    }
    return 0;
}

static void wpstr_assign(struct wpstr* wpstr, char* str){
    wpstr->str = str;
    wpstr->len = str == NULL ? 0 : strlen(str);
}


static struct wp_node* wp_alloc_node(enum map_type type, const char* path){
	struct wpnode* new_node = NULL;

    new_node = (struct wpnode*)kmalloc(sizeof(struct wpnode), GFP_ATOMIC);
    if(new_node == NULL){
		printk("kmalloc new wpnode fail\n");
        return NULL;
	}
    
}


static bool add_watch_path(enum wp_type type, char* path){
	struct wpnode* new_node = NULL;
	struct wpnode* tmp_node = NULL;

    if(type == WP_START)
        return false;

    tmp_node = &watchpath;

	while(tmp_node != NULL){
        

    }
    
}

// buffer: type|path
int add_watch_paths(const char __user* buffer, size_t size):
	int rc = -1;

	enum wp_type type = WP_START;

    char* content = NULL;
    char args[512] = {0};
	int args_size = size-1;
	snprintf(args, sizeof(args), "%s", buffer+1);

    fullpath_kis(args, &args_size);

	rc = wp_path_analysis(args, &content);

	if(rc != 0){
		if(!content) kfree(content);
		return -1;
	}

	switch (buffer[0] & 0xFF)
	{
		case WATCH_ROOT:
			type = WP_ROOT;
			break;
		case WATCH_PATH:
			type = WP_PATH;
			break;
		case WATCH_FILE:
			type = WP_FILE;
			break;
		case WATCH_SUFFIX:
			type = WP_SUFFIX;
			break;
		case WATCH_NOT_PATH:
			type = WP_NOT_PATH;
			break;
		case WATCH_NOT_FILE:
			type = WP_NOT_FILE;
			break;
		case WATCH_NOT_SUFFIX:
			type = WP_NOT_SUFFIX;
			break;
		case WATCH_FINISH:
			printk("-------------------------------------\n");
			
			printk("-------------------------------------\n");
			wpath_ready = true;
			return 0;
		default:
			break;
	}

	printk("type: %d, path: %s\n", type, content);

	
	
}
