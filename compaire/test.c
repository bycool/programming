#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	char** buf = (char**)malloc(sizeof(char*)*3);
	printf("&buf: %p\n", buf);
	printf("&buf[0]: %p\n", &buf[0]);
	printf("&buf[1]: %p\n", &buf[1]);
	printf("&buf[2]: %p\n", &buf[2]);

	buf[0] = (char*)malloc(3*sizeof(char));
	strcpy(buf[0], "12");

	buf[1] = (char*)malloc(3*sizeof(char));
	strcpy(buf[1], "23");
	buf[2] = (char*)malloc(3*sizeof(char));
	strcpy(buf[2], "34");
	free(buf[0]);
	free(buf[1]);
	free(buf[2]);
	free(buf);
}
