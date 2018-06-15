#include <linux/version.h>
#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/file.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/dcache.h>
#include <linux/sched.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/nfs_fs.h>
#include <linux/audit.h>
#include <linux/mount.h>
#include <linux/fs_struct.h>

/*
 * 该文件包含:
 * 		1.旧系统调用函数的函数指针定义，如：sys_mkdir_t是一个函数指针类型。
 *		2.新系统调用函数的函数声明。
 */



//func pointer type declaration
typedef asmlinkage long (*sys_mkdir_t)(const char __user* pathname, int mode);
typedef asmlinkage long (*sys_rmdir_t)(const char __user *pathname);


//new function declaration
asmlinkage long nsys_mkdir(const char __user* pathname, int mode);
asmlinkage long nsys_rmdir(const char __user *pathname);
