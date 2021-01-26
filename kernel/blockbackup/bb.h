



/*
 *  |             64                    |
 *  |sector_start|,|sector_len|,|ruleids|
 *  | max: 10    |1| max: 6   |1|  46   |
 *  |  18                       |
 */

#define CTRL_SET_RULE_STATE
#define CTRL_ADD_RULE
#define CTRL_SET_RULE_END

#define DISK_NAME_LEN 32

#define BB_DATA_RELAY_FILENAME "bbdata"
#define BB_DATA_SUBBUF_LEN  64
#define BB_DATA_SUBBUF_CNT  1024*1024
#define BB_DATA_RELAY_BUFSIZE 1024*1024*64  //64M

#define BB_CTRL_RELAY_FILENAME "bbctrl"
#define BB_CTRL_RELAY_BUFSIZE 1024*4

struct bbnode;


int rulists_set_finish(void);
void cleanup_rulist(void);
int append_rule_to_rulist(int ruleno, int major, int first_minor, int partno, char* disk_name, unsigned long sector_s, unsigned long sector_e);
int rulists_set_finish(void);
void display_rulist(struct bbnode* rule);

int bbrelay_init(void);
int bb_relay_write(char* data, int size);
void bbrelay_exit(void);

int bbdev_get_devinfo(char* devpath, int* major, int* first_minor, int* partno, char* disk_name, unsigned long* sector_s, unsigned long* sector_e);
int bbdev_hook_mrf(char* devpath);
int bbdev_unhook_mrf(char* devpath);
