#include <linux/init.h>
#include <asm/unistd.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/mount.h>
#include <linux/path.h>
#include <linux/fs.h>


void get_inode(void){
	char* path_name = "/home/teanee/programming/kernel/checkfunc/Makefile";


/*	unsigned long fileinode = -1;
	struct path path;
	kern_path(path_name, LOOKUP_FOLLOW, &path);
//	inode = path.dentry->d_inode;
	fileinode = path.dentry->d_inode->i_ino;
	printk("path : %s ,inode: %lu\n", path_name, fileinode);
*/
    struct inode *inode;
    struct path path;
    kern_path(path_name, LOOKUP_FOLLOW, &path);
	path_put(&path);
    inode = path.dentry->d_inode;
    printk("Path name : %s, inode :%lu\n", path_name, inode->i_ino);
}


static int __init checkfunc_init(void){
	printk("checkfunc mod init\n");

	get_inode();

	return 0;
}

static void __exit checkfunc_exit(void){
	printk("checkfunc mod exit\n");
}

module_init(checkfunc_init);
module_exit(checkfunc_exit);

MODULE_LICENSE("GPL");
