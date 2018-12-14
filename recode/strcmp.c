#include <stdio.h>
#include <string.h>

int main(){
	char str1[10] = "abc";
	int rc = strcmp(str1, "abc");
	if(rc == 0){
		printf("str1:%s\n",str1);
	}
}
