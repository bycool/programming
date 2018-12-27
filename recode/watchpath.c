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

static monitor_rule* rule_starta = {-1,	0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL};





