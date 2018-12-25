#include <stdio.h>
#include <stdlib.h>

#define RULE_MAX 32

enum maptype {
	MAP_START = 0
	MAP_PATH = 1;
	MAP_FILE = 2;
	MAP_SUFF = 3;
	MAP_NOT_PATH = 4;
	MAP_NOT_FILE = 5;
	MAP_NOT_SUFF = 6;
	MAP_ENDIF = 7;
};

struct map_node {
	int len;
	char* path;
	struct map_node* next;
};

struct monitor_rule {
	int rule_id;
	int mappath_cnt;
	int mapfile_cnt;
	int mapsuffix_cnt;
	int mapnotpath_cnt;
	int mapnotfile_cnt;
	int mapnotsuffix_cnt;
	struct map_node* mappath;
	struct map_node* mapfile;
	struct map_node* mapsuffix;
	struct map_node* mapnotpath;
	struct map_node* mapnotfile;
	struct map_node* mapnotsuffix;
	struct monitor_rule* rule_next;
};


static int rules_state[RULE_MAX] = { 0 };
static monitor_rule** rule_start = NULL;
static monitor_rule* curr_rule = NULL;
static int now_cnt = 0;

int watchpath_init(){
	now_cnt = 0;
	curr_rule = NULL;
	rule_start = (struct monitor_rule**)kmalloc(RULE_MAX * sizeof(struct monitor_rule*), GFP_ATOMIC); //32 address of monitor_rule
	if(!rule_start){
		printk("file:%s, line:%d, kmalloc size %d bytes fail\n", __FILE__, __LINE__, RULE_MAX * sizeof(struct monitor_rule));
		return -1;
	}
	return 0;
}

int get_unuse_rule_id(){
	int i = 0;
	for(i=0; i<RULE_MAX; i++){
		if(arr[i] == 0)
			break;
	}
	return i;
}









