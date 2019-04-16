#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdarg.h>
#include <dlfcn.h>

enum optype {
	create, open, write, write
};

int hasextenname(const char  *filename)
{
    char *extenset[4]={"~",".swp",".swpx",".swx"};
    int index=0;
    for(index=0;index<4;index++)
    {
        if(strcmp(filename+strlen(filename)-strlen(extenset[index]),extenset[index])==0)
        {
            return 1;
        }
    }
    return 0;
}

int monitored(char* realpath){
	char* map_path = NULL;
	map_path = getenv("MAP_PATH");

	if(map_path){
		if(hasextenname(realpath)){
			return 0;
		}
		if(memcmp(map_path, realpath, strlen(map_path)) == 0){
			return 1;
		}
	}
	return 0;
}


ssize_t getrealpath(int fd, char* realpath, int size){
	ssize_t rc = -1;
	char buf[64];
	sprintf(buf, "/proc/self/fd/%d", fd);
	rc = readlink(buf, realpath, size);
	return rc;
}

int getnamebytime(char* timebuf){
	int rc = -1;
	struct timeval tv;
	rc = gettimeofday(&tv, NULL);
	sprintf(timebuf, "%.10d%.10d", tv.tv_sec, tv.tv_usec);
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
	int infofd = -1;
	static void* handle = NULL;
	int realpathlen = 0;
	char realpath[4096];
	char outpath[4096];
	char timebuf[32] = {0};

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_open = (OPEN)dlsym(handle,"open");
		libc_write = (WRITE)dlsym(handle, "write");
		libc_creat = (CREAT)dlsym(handle, "creat");
	}

	rc = libc_creat(pathname, mode);
	if(rc > 0){
		tmp = libc_open(pathname, O_RDONLY);
		if(tmp > 0){
			realpathlen = getrealpath(tmp, realpath, 4096);
			realpath[realpathlen] = 0;
			if(monitored(realpath)){
				strcpy(outpath, getenv("OUT_PATH"));
				getnamebytime(timebuf);
				strcat(outpath, timebuf);
				infofd = libc_open(outpath, O_CREAT | O_WRONLY, 0600);
				libc_write(infofd, realpath, strlen(realpath));
				close(infofd);
			}
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

	tmp = libc_open(oldpath, O_RDONLY);
	if(tmp>0){
		realpathlen = getrealpath(tmp, oldrealpath, 4096);
		oldrealpath[realpathlen] = 0;
		close(tmp);
	}

	rc = libc_rename(oldpath, newpath);
	if(rc == 0){
		tmp = libc_open(newpath, O_RDONLY);
		if(tmp>0){
			realpathlen = getrealpath(tmp, newrealpath, 4096);
			newrealpath[realpathlen] = 0;
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

	va_list ap;
	va_start(ap, 0);
	mode_t mode = va_arg(ap, mode_t);

	
#if 0
	return libc_open(path,flage, mode);
#else
	rc = libc_open(path,flage, mode);
	if(rc > 0){
		realpathlen = getrealpath(rc, realpath, 4096);
		realpath[realpathlen] = 0;
	}
	return rc;
#endif
}



ssize_t write(int fd, const void* buf, size_t count){
	int rc = -1;
	off_t offset = 0;
	static void *handle = NULL;

	int infofd = -1;
	char realpath[4096];
	char outpath[4096];
	char* outenv = NULL;
	char timebuf[32] = {0};
	int realpathlen = -1;

	if(!handle){
		handle = dlopen("libc.so.6", RTLD_LAZY);
		libc_open = (OPEN)dlsym(handle,"open");
		libc_write = (WRITE)dlsym(handle, "write");
	}

	rc = libc_write(fd, buf, count);
	if(rc>0){
		realpathlen = getrealpath(fd, realpath, 4096);
		realpath[realpathlen] = 0;
		offset = lseek(fd, 0, SEEK_CUR) - rc;
		if(monitored(realpath)){
			outenv = getenv("OUT_PATH");
			strcpy(outpath, outenv);
			getnamebytime(timebuf);
			strcat(outpath, timebuf);
			infofd = libc_open(outpath, O_CREAT | O_WRONLY, 0600);
			libc_write(infofd, realpath, strlen(realpath));
			close(infofd);
		}
	}
	return rc;
}
