#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/version.h>
#include <asm/unistd.h>
#include <linux/file.h>
//#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/dcache.h>
#include <linux/sched.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/nfs_fs.h>
#include <linux/audit.h>
#include <linux/mount.h>
#include <linux/fs_struct.h>
#include <linux/limits.h>
#include <asm-generic/atomic-long.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

#define DISK_NAME_LEN 32

#define BB_DATA_RELAY_FILENAME "bbdata"
#define BB_DATA_SUBBUF_LEN  64
#define BB_DATA_SUBBUF_CNT  1024*1024
#define BB_DATA_RELAY_BUFSIZE 1024*1024*64  //64M

#define BB_CTRL_RELAY_FILENAME "bbctrl"
#define BB_CTRL_RELAY_BUFSIZE 1024*4

struct bbnode {
	int ruleno ;
	int major ;
	int first_minor ;
	int partno ;
	char disk_name[DISK_NAME_LEN] ;
	unsigned long sector_s ;
	unsigned long sector_e ;
	struct bbnode* next ;
};

int bbdev_setblk_mrf_bypath(const char* devpath) ;
int bbdev_resetblk_mrf_bypath(const char* devpath) ;
int bbdev_get_devinfo(char* devpath, int* major, int* first_minor, int* partno,
                            char* disk_name, unsigned long* sector_s, unsigned long* sector_e) ;

int append_rule_to_rulist(int ruleno, int major, int first_minor, int partno,
                                char* disk_name, unsigned long sector_s, unsigned long sector_e) ;
int bbfilter(char* devname, unsigned long sector_s, char* rulenos) ;
int rulists_set_finish(void) ;
void cleanup_rulist(void) ;

int bbrelay_init(void) ;
void bbrelay_exit(void) ;
int bb_relay_write(char* data, int size) ;
