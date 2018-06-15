#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#include <linux/relay.h>
#include <linux/debugfs.h>


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
    .sub_buf_size = 1024*16,
    .num_sub_buf = 1024*32,
    .is_mmap = false
};

static int subbuf_start_callback(struct rchan_buf *buf, 
                                 void *subbuf, 
                                 void *prev_subbuf, 
                                 size_t prev_padding){
    printk("chan_|data|control|.subbuf_start_callback\n");
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

static int remove_buf_file_callback(struct dentry* dentry){
    printk("chan_|data|control|.remove_buf_file_callback\n");
    debugfs_remove(dentry);
    return 0;
}

static struct rchan_callbacks chan_data_callback = {
    .subbuf_start     = subbuf_start_callback,
    .buf_mapped       = buf_mapped_callback,
    .buf_unmapped     = buf_unmapped_callback,
    .create_buf_file  = data_create_buf_file_callback,
    .remove_buf_file  = remove_buf_file_callback
};

int relay_write_to_channel(char* buffer, int buf_len){
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
    .sub_buf_size = 1024*4,
    .num_sub_buf = 1,
    .is_mmap = false
};

static struct dentry* control_create_buf_file_callback(const char* filename,
                                                       struct dentry* parent,
                                                       int mode,
                                                       struct rchan_buf* buf,
                                                       int *is_global){
    *is_global = 1;
    return debugfs_create_file(filename, parent, mode, buf, &control_file_operations);
}

static struct rchan_callbacks chan_control_callback = {
    .create_buf_file = control_create_buf_file_callback,
    .remove_buf_file = remove_buf_file_callback
};



static struct file_opertions control_file_operations = {
    .read = ,
    .write = 
};


/*--------------------------------     ------------------------------------*/

static int __init relay_init(void){
    printk("relay.init: user space interface file : %s\n", chan_data.base_pathname);
    chan_data.rchan = relay_open(chan_data.base_pathname, NULL, chan_data.sub_buf_size, chan_data.num_sub_buf, &chan_data_callback, NULL);
    if(chan_data.rchan == NULL){
        printk("relay open fail\n");
        return -1;
    }
    return 0;
}

static void __exit relay_exit(void){
    printk("relay.exit\n");
    if(chan_data.rchan){
        relay_close(chan_data.rchan);
        chan_data.rchan = NULL;
    }
}

module_init(relay_init);
module_exit(relay_exit);

MODULE_LICENSE("GPL");
