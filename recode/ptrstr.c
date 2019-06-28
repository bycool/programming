#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getstrm(char* s1, char* s2){
	char ss1[10] = {"123456789"};
	char ss2[10] = {"abcdefghi"};
	strcpy(s1, ss1);
	strcpy(s2, ss2);
}

void main(){
	char buf1[20];
	char buf2[20];

	getstrm(buf1, buf2);

	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);
}
