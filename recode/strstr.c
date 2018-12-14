#include <stdio.h>
#include <string.h>

int main(){
	char str1[16] = "hellow";
	char str2[16] = "hell";

	char* p = NULL;
	if(!strstr(str1, str2)){
		printf("get nothing\n");
	}else{
		printf("gotcha\n");
	}

	return 0;
}
