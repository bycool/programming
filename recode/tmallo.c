#include <stdio.h>
#include <stdlib.h>

int main(){
	char* ptr = (char*)malloc(10*1024*1024);
	char* ptr1 = (char*)malloc(10*1024*1024);
	char* ptr2 = (char*)malloc(10*1024*1024);
	char* ptr3 = (char*)malloc(10*1024*1024);
	char* ptr4 = (char*)malloc(10*1024*1024);
	char* ptr5 = (char*)malloc(10*1024*1024);
	char c = getchar();
	free(ptr);
	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);
	return 0;
}
