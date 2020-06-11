#include <stdio.h>
#include <stdlib.h>

void main(){
	char buf1[6] = {0}, buf2[6]={0};
	FILE *fp = fopen("./1.txt", "r+");
	if(fp == NULL){
		printf("open 1.txt failed!\n");
		return;
	}
	int n = fread(buf1, 2, 3, fp);
	printf("buf1: %s\n", buf1);
	n = fread(buf2, 3, 2, fp);
	printf("buf2: %s\n", buf2);
	fclose(fp);
}
