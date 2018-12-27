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
	printk("callsys_init: %lu\n", get_seconds());
	return 0;
}

static void __exit callsys_exit(void){
	printk("callsys_exit\n");
}

module_init(callsys_init);
module_exit(callsys_exit);

MODULE_LICENSE("GPL");
