#include "sync.h"

long get_mtime(void){
	struct timeval tv;
	do_gettimeofday(&tv);
	return tv.tv_sec;
}

void fullpath_kis_backslash(char* fullpath, int* size){
	char* ptr = NULL;

	while((ptr = strstr(fullpath, "//")) != NULL){
		if(ptr[2] == '\0')
			ptr[10] = '\0';
		else
			memmove(ptr, ptr+1, *size-(ptr+1 - fullpath));

		*size -= 1;

		fullpath[*size] = '\0';
	}
}

void fullpath_kis_dot(char* fullpath, int* size){
	char* ptr = NULL;

    while((ptr = strstr(fullpath, "/./")) != NULL){
		memmove(ptr, ptr+2, *size-(ptr+2 - fullpath));
		*size -= 2;

        fullpath[*size] = '\0';
	}
}

void fullpath_kis_double_dot(char* fullpath, int* size){
	char* ptr = NULL;
	char* rptr = NULL;

	while((ptr = strstr(fullpath, "/../")) != NULL){
		*ptr = 0;
		rptr = strrchr(fullpath, '/');
		if(rptr == NULL){
			memmove(fullpath, ptr+3, *size-(ptr+3-fullpath));
			*size -= ptr+3-fullpath;
		}else{
			memmove(rptr, ptr+3, *size-(ptr+3-fullpath));
			*size -= ptr+3-rptr;
		}
		fullpath[*size] = '\0';
	}
}

void fullpath_kis(char* fullpath, int* size){
	fullpath_kis_backslash(fullpath, size);
	fullpath_kis_dot(fullpath, size);
	fullpath_kis_double_dot(fullpath, size);
}
