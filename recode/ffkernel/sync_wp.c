
enum wp_type {
    WP_NULL = 0,
    WP_ROOT = 1,      //监控目录
    WP_PATH = 2,      //只监控目录下子目录
    WP_FILE = 3,      //只监控目录下的文件
    WP_SUFFIX = 4,    //只监控目录下的某个后缀文件
    WP_NOT_PATH = 5,  //不监控某个子目录
    WP_NOT_FILE = 6,  //不监控的某个文件
    WP_NOT_SUFFIX = 7,//不监控某个后缀文件
    WP_END = 8
};

static char* wp_str_type[] = {
    "WP_NULL", "WP_ROOT", "WP_PATH", "WP_FILE",
    "WP_SUFFIX", "WP_NOT_PATH", "WP_NOT_FILE", "WP_NOT_SUFFIX",
    "WP_END"
};

struct wp_str {
    char *str;
    int len;
};

typedef struct wpnode {
    enum wp_type type;

    struct wp_str content;

    struct wpnode* samelevel;
    struct wpnode* nextlevel; 
}wpnode;

static wpnode watchpath = {WP_NULL, {"/",1}, NULL, NULL};


