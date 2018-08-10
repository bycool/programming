/*
 * relay文件系统： chan_data:数据文件接口，driver向里面写入文件名称
 *                 chan_control:用于上层与driver进行交互
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/file.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

#include "sync.h"


struct channel_info {
    struct rchan* rchan;
    char* base_pathname;
    struct dentry* parent;
    size_t sub_buf_size;
    size_t num_sub_buf;
    bool is_mmap;
};

/*----------------------------------data----------------------------------*/
static struct channel_info chan_data = {
    .rchan = NULL,
    .base_pathname = "channel_data",
    .parent = NULL,
    .sub_buf_size = 1024 * 16, // 16k
    .num_sub_buf = 1024 * 32,  // 32k
    .is_mmap = false
};

static int subbuf_start_callback(struct rchan_buf *buf, 
                                 void *subbuf, 
                                 void *prev_subbuf, 
                                 size_t prev_padding){
    printk("chan_data.subbuf_start_callback\n");
    return 0;
}

static void buf_mapped_callback(struct rchan_buf* buf,
                                struct file *filp){
    chan_data.is_mmap = true;
    printk("chan_data.buf_mapped_callback\n");
}

static void buf_unmapped_callback(struct rchan_buf *buf,
                                  struct file *filp){
    chan_data.is_mmap = false;
    printk("chan_data.buf_unmapped_callback\n");
}

static struct dentry* data_create_buf_file_callback(const char *filename,
                                               struct dentry *parent,
                                               int mode,
                                               struct rchan_buf *buf,
                                               int *is_global){
    printk("chan_data.data_create_buf_file_callback\n");
    *is_global = 1;
    return debugfs_create_file(filename, mode, parent, buf, &relay_file_operations);
}

static int data_remove_buf_file_callback(struct dentry* dentry){
    printk("chan_data.remove_buf_file_callback\n");
    debugfs_remove(dentry);
    return 0;
}

static struct rchan_callbacks chan_data_callback = {
    .subbuf_start     = subbuf_start_callback,
    .buf_mapped       = buf_mapped_callback,
    .buf_unmapped     = buf_unmapped_callback,
    .create_buf_file  = data_create_buf_file_callback,
    .remove_buf_file  = data_remove_buf_file_callback
};

int relay_write_data(char* buffer, int buf_len){
	if(!chan_data.is_mmap){
		printk("relay file does not mmap to user space\n");
		return -1;
	}
	relay_write(chan_data.rchan, buffer, buf_len);
	return 0;
}

/*----------------------------------control----------------------------------*/
static struct channel_info chan_control = {
    .rchan = NULL,
    .base_pathname = "channel_control",
    .parent = NULL,
    .sub_buf_size = 1024*4, //4k
    .num_sub_buf = 1,
    .is_mmap = false
};

static ssize_t control_read(struct file* filep, char __user * buffer, size_t count, loff_t *ppos){
    printk("relay:control_read\n");

    return 0;
}

static ssize_t control_write(struct file* filep, const char __user * buffer, size_t count, loff_t *ppos){
    printk("relay:control_write\n");

    return 0;
}

static struct file_operations control_file_operations = 
{
    .read = control_read,
    .write = control_write
};

static struct dentry* control_create_buf_file_callback(const char* filename,
                                                       struct dentry* parent,
                                                       int mode,
                                                       struct rchan_buf* buf,
                                                       int *is_global){
    printk("sydr create control_relay_file: %s\n", filename);
    *is_global = 1;
    return debugfs_create_file(filename, mode, parent, buf, &control_file_operations);
}

static int control_remove_buf_file_callback(struct dentry* dentry){
    if(dentry != NULL)
        debugfs_remove(dentry);
    printk("sydr remove control_relay_file\n");
    return 0;
}

static struct rchan_callbacks chan_control_callback = {
    .create_buf_file = control_create_buf_file_callback,
    .remove_buf_file = control_remove_buf_file_callback
};

/*-------------------------------- main  ------------------------------------*/

int relay_init(void){
    chan_data.rchan = relay_open(chan_data.base_pathname, NULL,
                                 chan_data.sub_buf_size, chan_data.num_sub_buf,
                                 &chan_data_callback, NULL);
    if(chan_data.rchan == NULL){ printk("relay[data] open fail\n"); return -1; }

    chan_control.rchan = relay_open(chan_control.base_pathname, NULL,
                                    chan_control.sub_buf_size, chan_control.num_sub_buf,
                                    &chan_control_callback, NULL);
    if(chan_control.rchan == NULL){ printk("relay[control] open fail\n"); return -1; }

    printk("relay.init\n");

    return 0;
}

void relay_exit(void){
    if(chan_data.rchan){
        relay_close(chan_data.rchan);
        chan_data.rchan = NULL;
    }
    if(chan_control.rchan){
        relay_close(chan_control.rchan);
        chan_control.rchan = NULL;
    }
    printk("relay.exit\n");
}
