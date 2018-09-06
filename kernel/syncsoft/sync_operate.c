#include "sync.h"

extern sys_open_t old_open;
extern sys_openat_t old_openat;
extern sys_creat_t old_creat;
extern sys_write_t old_write;
extern sys_writev_t old_writev;
extern sys_pwritev_t old_pwritev;
extern sys_pwrite64_t old_pwrite64;
extern sys_lseek_t old_lseek;
extern sys_close_t old_close;
extern sys_mkdir_t old_mkdir;
extern sys_unlink_t old_unlink;
extern sys_unlinkat_t old_unlinkat;
extern sys_link_t old_link;
extern sys_linkat_t old_linkat;
extern sys_symlink_t old_symlink;
extern sys_symlinkat_t old_symlinkat;
extern sys_rename_t old_rename;
extern sys_renameat_t old_renameat;
extern sys_truncate_t old_truncate;
extern sys_ftruncate_t old_ftruncate;
extern sys_rmdir_t old_rmdir;
extern sys_chown_t old_chown;
extern sys_lchown_t old_lchown;
extern sys_fchown_t old_fchown;
extern sys_fchownat_t old_fchownat;
extern sys_chmod_t old_chmod;
extern sys_fchmod_t old_fchmod;
extern sys_fchmodat_t old_fchmodat;

asmlinkage long nsys_open(const char __user* filename, int flag, int mode){
	printk("nsys_open\n");
	return old_open(filename, flag, mode);
}

asmlinkage long nsys_openat(int dfd, const char __user* pathname, int flag, int mode){
	return old_openat(dfd, pathname, flag, mode);
}

asmlinkage long nsys_creat(const char __user* pathname, int mode){
	return old_creat(pathname, mode);
}

asmlinkage long nsys_write(unsigned int fd, const char __user* buf, size_t len){
	return old_write(fd, buf, len);
}

asmlinkage long nsys_writev(unsigned long fd, const struct iovec __user* vec, unsigned long vlen){
	return old_writev(fd, vec, vlen);
}

asmlinkage long nsys_pwritev(unsigned long fd, const struct iovec __user* vec, unsigned long vlen,
                                         unsigned long pos_l, unsigned long pos_h){
	return old_pwritev(fd, vec, vlen, pos_l, pos_h);
}

asmlinkage long nsys_pwrite64(unsigned int fd, const char __user* buf, size_t count, loff_t pos){
	return old_pwrite64(fd, buf, count, pos);
}

asmlinkage long nsys_lseek(unsigned int fd, off_t offset, unsigned origin){
	return old_lseek(fd, offset, origin);
}

asmlinkage long nsys_close(unsigned int fd){
	return old_close(fd);
}

asmlinkage long nsys_mkdir(const char __user* pathname, int mode){
	printk("nsys_mkdir\n");
	return old_mkdir(pathname,mode);
}

asmlinkage long nsys_unlink(const char __user* pathname){
	return old_unlink(pathname);
}

asmlinkage long nsys_unlinkat(int dfd, const char __user* pathname, int flag){
	return old_unlinkat(dfd, pathname, flag);
}

asmlinkage long nsys_link(const char __user* oldname, const char __user* newname){
	return old_link(oldname, newname);
}

asmlinkage long nsys_linkat(int olddfd, const char __user* oldname, int newdfd, const char __user* newname, int flag){
	return old_linkat(olddfd, oldname, newdfd, newname, flag);
}

asmlinkage long nsys_symlink(const char __user* oldname, const char __user* newname){
	return old_symlink(oldname, newname);
}

asmlinkage long nsys_symlinkat(const char __user* oldname, int newdfd, const char __user* newname){
	return old_symlinkat(oldname, newdfd, newname);
}

asmlinkage long nsys_rename(const char __user* oldname, const char __user* newname){
	return old_rename(oldname, newname);
}

asmlinkage long nsys_renameat(int olddfd, const char __user* oldname, int newdfd, const char __user* newname){
	return old_renameat(olddfd, oldname, newdfd, newname);
}

asmlinkage long nsys_truncate(const char __user* pathname, long length){
	return old_truncate(pathname, length);
}

asmlinkage long nsys_ftruncate(unsigned int fd, unsigned long length){
	return old_ftruncate(fd, length);
}

asmlinkage long nsys_rmdir(const char __user* pathname){
	printk("nsys_rmdir\n");
	return old_rmdir(pathname);
}

asmlinkage long nsys_chown(const char __user* filename, uid_t user, gid_t group){
	return old_chown(filename, user, group);
}

asmlinkage long nsys_lchown(const char __user* filename, uid_t user, gid_t group){
	return old_lchown(filename, user, group);
}

asmlinkage long nsys_fchown(unsigned int fd, uid_t user, gid_t group){
	return old_fchown(fd, user, group);
}

asmlinkage long nsys_fchownat(int dfd, const char __user* filename, uid_t user, gid_t group, int flag){
	return old_fchownat(dfd, filename, user, group, flag);
}

asmlinkage long nsys_chmod(const char __user* filename, mode_t mode){
	return old_chmod(filename, mode);
}

asmlinkage long nsys_fchmod(unsigned int fd, mode_t mode){
	return old_fchmod(fd, mode);
}

asmlinkage long nsys_fchmodat(int dfd, const char __user* filename, mode_t mode){
	return old_fchmodat(dfd, filename, mode);
}
