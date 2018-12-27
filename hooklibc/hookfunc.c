#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>

/*
ssize_t      write(int, const void *, size_t);
typedef     int(*CHOWN)(const char *, uid_t, gid_t);
typedef     int(*FCHOWN)(int, uid_t, gid_t);
int          ftruncate(int, off_t);
int          lchown(const char *, uid_t, gid_t);
int          link(const char *, const char *);
off_t        lseek(int, off_t, int);
ssize_t      pwrite(int, const void *, size_t, off_t);
int          symlink(const char *, const char *);
int          truncate(const char *, off_t);
int          unlink(const char *);
int      fclose(FILE *);
FILE    *fopen(const char *restrict, const char *restrict);
int      pclose(FILE *);
int  creat(const char *, mode_t);
*/
typedef int(*OPEN)(const char *, int, ...);
typedef ssize_t(*WRITE)(int, const void*, size_t);

int open(const char* path, int flage,...){
	static void *handle = NULL;
	static OPEN libc_open = NULL;
    if(!handle){
        handle = dlopen("libc.so.6", RTLD_LAZY);
        libc_open = (OPEN)dlsym(handle, "open");
    }
	printf("hack open\n");
	return libc_open(path,flage);
}



ssize_t write(int fd, const void* buf, size_t count){
	int rc = -1;
	off_t offset = 0;
	static void *handle = NULL;
	static WRITE libc_write = NULL;

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_write = (WRITE)dlsym(handle, "write");
	}
	rc = libc_write(fd, buf, count);
	if(rc>0){
		offset = lseek(fd, 0, SEEK_CUR) - rc;
		printf("offset=%lu\n", offset);
	}
	return rc;
}
