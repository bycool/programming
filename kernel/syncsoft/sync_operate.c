#include "sync_syscall.h"

extern sys_mkdir_t old_mkdir;
extern sys_rmdir_t old_rmdir;

asmlinkage long nsys_mkdir(const char __user* pathname, int mode){
	printk("nsys_mkdir\n");
	return old_mkdir(pathname,mode);
}

asmlinkage long nsys_rmdir(const char __user* pathname){
	printk("nsys_rmdir\n");
	return old_rmdir(pathname);
}
