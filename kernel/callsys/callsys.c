#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/syscalls.h>

#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/minix_fs.h>
#include <linux/ext2_fs.h>
#include <linux/romfs_fs.h>
#include <linux/initrd.h>
#include <linux/sched.h>
#include <linux/freezer.h>

#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/mm.h>





static int __init callsys_init(void){

	struct file *filep = NULL;
	mm_segment_t old_fs;
	loff_t pos;
	char* path = "/home/teanee/7.txt";
	char buf[7] = "123456";

	filep = filp_open(path, O_WRONLY|O_CREAT, 0600);
	old_fs = get_fs();
	set_fs(KERNEL_DS);
	pos = 0;
	vfs_write(filep, buf, strlen(buf), &pos);
	set_fs(old_fs);
	filp_close(filep, NULL);
	printk("callsys_init\n");
	return 0;
}

static void __exit callsys_exit(void){
	printk("callsys_exit\n");
}

module_init(callsys_init);
module_exit(callsys_exit);

MODULE_LICENSE("GPL");
