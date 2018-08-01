#include "nsysfunc.h"

extern sys_open_t old_open;
extern sys_write_t old_write;
extern sys_mkdir_t old_mkdir;
extern sys_rmdir_t old_rmdir;

asmlinkage long nsys_open(){

}

asmlinkage long nsys_mkdir(const char __user* pathname, int mode){
	printk("nsys_mkdir\n");
	return old_mkdir(pathname,mode);
}

asmlinkage long nsys_rmdir(const char __user* pathname){
	printk("nsys_rmdir\n");
	return old_rmdir(pathname);
}

asmlinkage long nsys_write(unsigned int fd, const char __user* buf, size_t count){
	return old_write(fd, buf, count);
}
