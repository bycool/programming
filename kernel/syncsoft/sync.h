#include <linux/version.h>
#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/file.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/dcache.h>
#include <linux/sched.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/nfs_fs.h>
#include <linux/audit.h>
#include <linux/mount.h>
#include <linux/limits.h>
#include <linux/fs_struct.h>

#include "sync_operate.h"

/* utils */
void fullpath_kis_backslash(char* fullpath, int* size);
void fullpath_kis_dot(char* fullpath, int* size);
void fullpath_kis_double_dot(char* fullpath, int* size);
void fullpath_kis(char* fullpath, int* size);

/* relay */
int relay_init(void);
void relay_exit(void);
int relay_write_data(char* buffer, int buf_len);

/* hook */
int sync_hook_init(void);
void sync_unhook_exit(void);

