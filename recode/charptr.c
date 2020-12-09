#include <stdio.h>

void main(){
	char buf[16] = "1234567890";
	char* ptr = NULL;

	ptr = buf;
	printf("%s\n", ptr);
	ptr = &buf[1];
	printf("%s\n", ptr);
}
