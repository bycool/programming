#include <stdio.h>



void main(){
	FILE* fp = fopen("1.txt", "r");
	if(!fp) {printf("open 1.txt fail\n"); return;}
	long fpos = ftell(fp);
	printf("%lu\n", fpos);
	fclose(fp);
}
