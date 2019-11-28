#include <stdio.h>

void main(){
	FILE* fp = fopen("fprin.log", "a");
	if(fp==NULL){
		printf("fopen error\n");
		return;
	}
	fprintf(fp, "%s", "fopen ok\n");
	fprintf(fp, "fopen ok 2\n");
	fclose(fp);
}
