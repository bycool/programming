#ifndef __KERNEL__
#define __KERNEL__
#endif

#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/kthread.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

static struct rchan *relay_rchan = NULL;
struct dentry *dir = NULL;

static int write_start(void);

static int subbuf_start_callback(struct rchan_buf *buf, void *subbuf, void *prev_subbuf, unsigned int prev_padding)
{
	static int warned;
	if (!relay_buf_full(buf))
		return 1;
	if (!warned) {
		warned = 1;
		printk("relay_buf_full!\n");
	}
	
	return 0;
}

static void buf_mapped_callback(struct rchan_buf *buf,struct file* pfile){
	printk("buf_mapped_callback\n");
}

static void buf_unmapped_callback(struct rchan_buf* rbuf, struct file* pfile){
	printk("buf_unmapped_callback\n");
}

static struct dentry * create_buf_file_callback(const char *filename, struct dentry *parent, umode_t mode, struct rchan_buf *buf, int *is_global)
{
	*is_global = 1;
	return debugfs_create_file(filename, mode, parent, buf, &relay_file_operations);
}

static int remove_buf_file_callback(struct dentry *dentry)
{
	printk("dentry remove!\n");
	debugfs_remove(dentry);
	return 0;
}

static struct rchan_callbacks relay_callbacks =
{
	.subbuf_start	 = subbuf_start_callback,
	.buf_mapped		 = buf_mapped_callback,
	.buf_unmapped	 = buf_unmapped_callback,
	.create_buf_file = create_buf_file_callback,
	.remove_buf_file = remove_buf_file_callback,
};

static int __init relay_init(void)
{
	/*  create folder relay_test_dir  */
	dir = debugfs_create_dir("relay_test_dir", NULL);
	if (NULL == dir){
		printk("Create directory failed!\n");
		return -1;
	}
	
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
	relay_rchan = relay_open("cpu", dir, 1024*1024*1024, 1, &relay_callbacks, NULL);
#else   
	relay_rchan = relay_open("cpu", dir, 1024, 1, &relay_callbacks);
#endif

    if(NULL == relay_rchan){  
        printk("relay_open() failed.\n");  
        return -1;  
    }

	write_start();

/*	
	for(count = 0; count < 10000; count++){
		sprintf(buffer, "cnt = %d\n", count);
		relay_write(relay_rchan, buffer, strlen(buffer));
	}
*/
	return 0;  
}

static int kern_write_relay(void* args){
	int count ;
	char buf[20];

	for(count = 0; count < 1000000; count++){
		sprintf(buf, "cnt = %d\n", count);
		relay_write(relay_rchan, buf, strlen(buf));
	}
	return 0;
}

static int write_start(void){
	static struct task_struct* thd_write = NULL;
	thd_write = kthread_run(kern_write_relay, NULL, "write_start");
	if(thd_write == NULL){
		return -1;
	}
	return 0;
}

static void __exit relay_exit(void)
{
	if(relay_rchan) {  
        relay_close(relay_rchan);
		
		if (dir!=NULL){
			debugfs_remove(dir);		
			dir = NULL;
		}
		
        relay_rchan = NULL;  
    }
}
 
module_init(relay_init);
module_exit(relay_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dynamic <cancanfairy@sina.com>");
MODULE_DESCRIPTION("Relay Test");
