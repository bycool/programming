#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h> 
#include <linux/mount.h>
#include <linux/path.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/namei.h>



// it showes how the kernel module get the

// file info, like inode, via kern_path ()



char *path_name = "/home/wangdachuan/wtest/wind.c";



int myinit(void)

{
	struct inode *inode;
	struct path path;
	kern_path(path_name, LOOKUP_FOLLOW, &path);
	inode = path.dentry->d_inode;
	printk("Path name : %s, inode :%lu\n", path_name, inode->i_ino);
	return 0;

}





void myexit(void)

{return;

}



module_init(myinit); 

module_exit(myexit);



//MODULE_AUTHOR("Shubham");

//MODULE_DESCRIPTION("Module to get inode from path");

MODULE_LICENSE("GPL");

MODULE_LICENSE("GPL v2");

