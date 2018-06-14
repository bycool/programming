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

static struct channel_info chanone = {
    .rchan = NULL,
    .base_pathname = "channelone",
    .parent = NULL,
    .sub_buf_size = 1024*1024,
    .num_sub_buf = 1,
    .is_mmap = false
};

static int subbuf_start_callback(struct rchan_buf *buf, 
                                 void *subbuf, 
                                 void *prev_subbuf, 
                                 size_t prev_padding){
    printk("chanone.subbuf_start_callback\n");
    return 0;
}

static void buf_mapped_callback(struct rchan_buf* buf,
                                struct file *filp){
    chanone.is_mmap = true;
    printk("chanone.buf_mapped_callback\n");
}

static void buf_unmapped_callback(struct rchan_buf *buf,
                                  struct file *filp){
    chanone.is_mmap = false;
    printk("chanone.buf_unmapped_callback\n");
}

static struct dentry* create_buf_file_callback(const char *filename,
                                               struct dentry *parent,
                                               int mode,
                                               struct rchan_buf *buf,
                                               int *is_global){
    printk("chanone.create_buf_file_callback\n");
    *is_global = 1;
    return debugfs_create_file(filename, mode, parent, buf, &relay_file_operations);
}

static int remove_buf_file_callback(struct dentry* dentry){
    printk("chanone.remove_buf_file_callback\n");
    debugfs_remove(dentry);
    return 0;
}

static struct rchan_callbacks chanone_callback = {
    .subbuf_start     = subbuf_start_callback,
    .buf_mapped       = buf_mapped_callback,
    .buf_unmapped     = buf_unmapped_callback,
    .create_buf_file  = create_buf_file_callback,
    .remove_buf_file  = remove_buf_file_callback,
};

int relay_write_to_channel(char* buffer, int buf_len){
	if(!chanone.is_mmap){
		printk("relay file does not mmap to user space\n");
		return -1;
	}
	return relay_write(chanone.rchan, buffer, buf_len);
}

static int __init relay_init(void){
    printk("relay.init: user space interface file : %s\n", chanone.base_pathname);
    chanone.rchan = relay_open(chanone.base_pathname, NULL, chanone.sub_buf_size, chanone.num_sub_buf, &chanone_callback, NULL);
    if(chanone.rchan == NULL){
        printk("relay open fail\n");
        return -1;
    }
    return 0;
}

static void __exit relay_exit(void){
    printk("relay.exit\n");
    if(chanone.rchan){
        relay_close(chanone.rchan);
        chanone.rchan = NULL;
    }
}

module_init(relay_init);
module_exit(relay_exit);

MODULE_LICENSE("GPL");
