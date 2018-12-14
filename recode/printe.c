#include <stdio.h>

int main(){
	printf("hello world!\n");
	write(0, "hello world!\n", 13);
	return 0;
}
