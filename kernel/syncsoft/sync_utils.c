#include "sync.h"

void fullpath_kis_backslash(char* fullpath, int* size){
	char* ptr = NULL;

	while((ptr = strstr(fullpath, "//")) != NULL){
		if(ptr[2] = '\0')
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
	
}
