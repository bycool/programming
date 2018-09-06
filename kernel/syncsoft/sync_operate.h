/*
 * 该文件包含:
 * 		1.旧系统调用函数的函数指针定义，如：sys_mkdir_t是一个函数指针类型。
 *		2.新系统调用函数的函数声明。
 */
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

//func pointer type declaration
typedef asmlinkage long (*sys_open_t)(const char __user* pathname, int flag, int mode);
typedef asmlinkage long (*sys_openat_t)(int dfd, const char __user* pathname, int flag, int mode);
typedef asmlinkage long (*sys_creat_t)(const char __user* pathname, int mode);
typedef asmlinkage long (*sys_write_t)(unsigned int fd, const char __user* buf, size_t len);
typedef asmlinkage long (*sys_writev_t)(unsigned long fd, const struct iovec __user* vec, unsigned long vlen);
typedef asmlinkage long (*sys_pwritev_t)(unsigned long fd, const struct iovec __user* vec, unsigned long vlen,
										 unsigned long pos_l, unsigned long pos_h);
typedef asmlinkage long (*sys_pwrite64_t)(unsigned int fd, const char __user* buf, size_t count, loff_t pos);
typedef asmlinkage long (*sys_lseek_t)(unsigned int fd, off_t offset, unsigned origin);
typedef asmlinkage long (*sys_close_t)(unsigned int fd);
typedef asmlinkage long (*sys_mkdir_t)(const char __user* pathname, int mode);
typedef asmlinkage long (*sys_unlink_t)(const char __user* pathname);
typedef asmlinkage long (*sys_unlinkat_t)(int dfd, const char __user* pathname, int flag);
typedef asmlinkage long (*sys_link_t)(const char __user* oldname, const char __user* newname);
typedef asmlinkage long (*sys_linkat_t)(int olddfd, const char __user* oldname, int newdfd, const char __user* newname, int flag);
typedef asmlinkage long (*sys_symlink_t)(const char __user* oldname, const char __user* newname);
typedef asmlinkage long (*sys_symlinkat_t)(const char __user* oldname, int newdfd, const char __user* newname);
typedef asmlinkage long (*sys_rename_t)(const char __user* oldnm, const char __user* newnm);
typedef asmlinkage long (*sys_renameat_t)(int olddfd, const char __user* oldname, int newdfd, const char __user* newname);
typedef asmlinkage long (*sys_truncate_t)(const char __user* pathname, long length);
typedef asmlinkage long (*sys_ftruncate_t)(unsigned int fd, unsigned long length);
typedef asmlinkage long (*sys_rmdir_t)(const char __user *pathname);
typedef asmlinkage long (*sys_chown_t)(const char __user* filename, uid_t user, gid_t group);
typedef asmlinkage long (*sys_lchown_t)(const char __user* filename, uid_t user, gid_t group);
typedef asmlinkage long (*sys_fchown_t)(unsigned int fd, uid_t user, gid_t group);
typedef asmlinkage long (*sys_fchownat_t)(int dfd, const char __user* filename, uid_t user, gid_t group, int flag);
typedef asmlinkage long (*sys_chmod_t)(const char __user* filename, mode_t mode);
typedef asmlinkage long (*sys_fchmod_t)(unsigned int fd, mode_t mode);
typedef asmlinkage long (*sys_fchmodat_t)(int dfd, const char __user* filename, mode_t mode);


//new function declaration
asmlinkage long nsys_mkdir(const char __user* pathname, int mode);
asmlinkage long nsys_rmdir(const char __user *pathname);
