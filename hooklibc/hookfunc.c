#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <dlfcn.h>

ssize_t getrealpath(int fd, char* realpath, int size){
	ssize_t rc = -1;
	char buf[64];
	sprintf(buf, "/proc/self/fd/%d", fd);
	rc = readlink(buf, realpath, size);
	return rc;
}

typedef int(*CREAT)(const char *, mode_t);
typedef int(*OPEN)(const char *, int, ...);
typedef int(*OPENAT)(int, const char*, int, ...);
typedef ssize_t(*WRITE)(int, const void*, size_t);
typedef int(*RENAME)(const char *, const char *);

static CREAT libc_creat = NULL;
static OPEN libc_open = NULL;
static OPENAT libc_openat = NULL;
static WRITE libc_write = NULL;
static RENAME libc_rename = NULL;

int creat(const char *pathname, mode_t mode){
	int rc = -1;
	int tmp = -1;
	static void* handle = NULL;
	int realpathlen = 0;
	char realpath[4096];

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_open = (OPEN)dlsym(handle,"open");
		libc_creat = (CREAT)dlsym(handle, "creat");
	}
//	printf("hack creat\n");

	rc = libc_creat(pathname, mode);
	if(rc > 0){
		tmp = libc_open(pathname, O_RDONLY);
		if(tmp > 0){
			realpathlen = getrealpath(tmp, realpath, 4096);
			realpath[realpathlen] = 0;
		//	printf("creat.realpath: %s\n", realpath);
			close(tmp);
		}
	}
	return rc;
}

int rename(const char *oldpath, const char *newpath){
	int rc = -1;
	int tmp = -1;
	static void *handle = NULL;
	int realpathlen = 0;
	char oldrealpath[4096];
	char newrealpath[4096];

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_rename = (RENAME)dlsym(handle, "rename");
		libc_open = (OPEN)dlsym(handle, "open");
	}
//	printf("hack rename\n");

	tmp = libc_open(oldpath, O_RDONLY);
	if(tmp>0){
		realpathlen = getrealpath(tmp, oldrealpath, 4096);
		oldrealpath[realpathlen] = 0;
	//	printf("rename.oldrealpath: %s\n", oldrealpath);
		close(tmp);
	}

	rc = libc_rename(oldpath, newpath);
	if(rc == 0){
		tmp = libc_open(newpath, O_RDONLY);
		if(tmp>0){
			realpathlen = getrealpath(tmp, newrealpath, 4096);
			newrealpath[realpathlen] = 0;
		//	printf("rename.newrealpath: %s\n", newrealpath);
			close(tmp);
		}
	}
	return rc;
}

int openat(int dirfd, const char *pathname, int flags, ...){
	int rc = -1;
	static void* handle = NULL;

	char realpath[4096];

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_openat = (OPENAT)dlsym(handle, "openat");
	}
//	printf("hack openat\n");

	va_list ap;
	va_start(ap, 0);
	mode_t mode = va_arg(ap, mode_t);

	return libc_openat(dirfd, pathname, flags, mode);

	
}

int open(const char* path, int flage, ...){
	int rc = -1;
	static void *handle = NULL;
	char realpath[4096];
	int realpathlen = -1;
    if(!handle){
        handle = dlopen("libc.so.6", RTLD_LAZY);
        libc_open = (OPEN)dlsym(handle, "open");
    }
//	printf("hack open\n");

	va_list ap;
	va_start(ap, 0);
	mode_t mode = va_arg(ap, mode_t);

//	printf("open.mode=%d\n", mode);
	
#if 0
	return libc_open(path,flage, mode);
#else
	rc = libc_open(path,flage, mode);
	if(rc > 0){
		realpathlen = getrealpath(rc, realpath, 4096);
		realpath[realpathlen] = 0;
	//	printf("open.realpath: %s\n", realpath);
	}
	return rc;
#endif
}



ssize_t write(int fd, const void* buf, size_t count){
	int rc = -1;
	off_t offset = 0;
	static void *handle = NULL;

	char realpath[4096];
	int realpathlen = -1;

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_write = (WRITE)dlsym(handle, "write");
	}
//	printf("hack write\n");

	char* map_path = NULL;
	map_path = getenv("MAP_PATH");
	if(map_path)
	//	printf("MAP_PATH: %s\n", map_path);

	rc = libc_write(fd, buf, count);
	if(rc>0){
		realpathlen = getrealpath(fd, realpath, 4096);
		realpath[realpathlen] = 0;
		offset = lseek(fd, 0, SEEK_CUR) - rc;
	//	printf("write.realpath = %s\n", realpath);
	//	printf("write.offset=%lu\n", offset);
	//	printf("write.content=%s\n", buf);
	//	printf("write.size = %d\n", count);
	}
	return rc;
}
