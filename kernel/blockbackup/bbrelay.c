#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/version.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

#define BB_DATA_RELAY_FILENAME "bbdata"
#define BB_DATA_SUBBUF_LEN	64
#define BB_DATA_SUBBUF_CNT  1024*1024
#define BB_DATA_RELAY_BUFSIZE 1024*1024*64  //64M

#define BB_CTRL_RELAY_FILENAME "bbctrl"
#define BB_CTRL_RELAY_BUFSIZE 1024*4

struct rchan* relay_data = NULL;
bool data_mapped = false;
atomic_t data_ready_sub_cnt = ATOMIC_INIT(0);

struct rchan* relay_ctrl = NULL;

static int bb_relay_output(struct rchan* channel, char* data, int size){
	struct rchan_buf* rbuf = channel->buf[0];

	if(atomic_read(&data_ready_sub_cnt)== BB_DATA_SUBBUF_CNT){
		printk("data subbuf cnt max\n");
		return 1;
	}

	if(rbuf->data - rbuf->start == BB_DATA_SUBBUF_LEN * BB_DATA_SUBBUF_CNT)
		rbuf->data = rbuf->start;

	atomic_add_return(1, &data_ready_sub_cnt);

	memcpy(rbuf->data, data, size);
	rbuf->data += BB_DATA_SUBBUF_LEN;

	return 0;
}

int bb_relay_write(char* data, int size){
	if( relay_data == NULL || data_mapped == false)
		return 0;

	return bb_relay_output(relay_data, data, size);
}




static struct dentry* data_create_buf_file_callback(const char *filename,
													struct dentry* parent,
												#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
													umode_t mode,
												#else
													int mode,
												#endif
													struct rchan_buf *buf,
													int *is_global) {
	if(is_global != NULL)
		*is_global = 1;
	return debugfs_create_file(filename, 0666, parent, buf, &relay_file_operations);
}
static void data_buf_mapped(struct rchan_buf* rbuf, struct file* pfile) {
	if( relay_data!=NULL )
		relay_reset(relay_data);

	atomic_set(&data_ready_sub_cnt, 0);

	data_mapped = true;
	printk("data_relay mapped\n");
}
static void data_buf_unmapped(struct rchan_buf* rbuf, struct file* pfile) {
//	if(pfile->f_count.counter > 2)
//		return ;
	data_mapped = false;
}
static int remove_buf_file_callback(struct dentry* dentry) {
	debugfs_remove(dentry);
	return 0;
}
static struct rchan_callbacks data_callback = {
	.buf_mapped	= data_buf_mapped,
	.buf_unmapped = data_buf_unmapped,
	.create_buf_file = data_create_buf_file_callback,
	.remove_buf_file = remove_buf_file_callback
};


static ssize_t ctrl_file_read(struct file* filep, char __user* user_buffer, size_t count, loff_t* ppos){
	char buffer[128];
	int len;
	len = copy_from_user(buffer, user_buffer, count);

	if((buffer[0] == '1')){
		return atomic_read(&data_ready_sub_cnt);
	}

	printk("ctrl_file_read\n");
	return 0;
}
static ssize_t ctrl_file_write(struct file* filep, const char  __user* user_buffer, size_t count, loff_t* ppos){
	char buffer[128];
	int len;
//	int ruleno;
	len = copy_from_user(buffer, user_buffer, count);

	switch(buffer[0])
	{
		case '1':  //insert rule
		case '2':  //insert rule end
		case '3':  //quit
		case '4':  //stop
		case '5':  //start
			break;
	}
	printk("ctrl_file_write\n");
	return 0;
}
static struct file_operations ctrl_relay_file_operations = {
	.read = ctrl_file_read,
	.write = ctrl_file_write
};
static struct dentry* ctrl_create_buf_file_callback(const char* filename,
													struct dentry* parent,
												#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
													umode_t mode,
												#else
													int mode,
												#endif
													struct rchan_buf* buf,
													int* is_global) {
	if(is_global != NULL)
		*is_global = 1;
	return debugfs_create_file(filename, 0666, parent, buf, &ctrl_relay_file_operations);
}
static struct rchan_callbacks ctrl_callback = {
	.create_buf_file = ctrl_create_buf_file_callback,
	.remove_buf_file = remove_buf_file_callback
};


int __init bbrelay_init(void) {
//int bbrelay_init(void) {
	relay_data = relay_open(BB_DATA_RELAY_FILENAME, NULL, BB_DATA_SUBBUF_LEN * BB_DATA_SUBBUF_CNT, 1, &data_callback, NULL);
	relay_ctrl = relay_open(BB_CTRL_RELAY_FILENAME, NULL, BB_CTRL_RELAY_BUFSIZE, 1, &ctrl_callback, NULL);

	if(!relay_data && !relay_ctrl)
		goto fail;

	printk("[block backup relay module init ok]\n");

	return 0;

fail:
	if(relay_data){
		relay_close(relay_data);
		relay_data = NULL;
		printk("relay create ctrl relay file fail\n");
	}
	if(relay_ctrl){
		relay_close(relay_ctrl);
		relay_ctrl = NULL;
		printk("relay create data relay file fail\n");
	}

	printk("[block backup relay module init fail]\n");

	return -1;
}

void __exit bbrelay_exit(void) {
//void bbrelay_exit(void) {
	if(relay_data){
		relay_close(relay_data);
		relay_data = NULL;
	}
	if(relay_ctrl){
		relay_close(relay_ctrl);
		relay_ctrl = NULL;
	}
	printk("[block backup relay module exit]\n");
}

module_init(bbrelay_init);
module_exit(bbrelay_exit);

MODULE_LICENSE("GPL");
