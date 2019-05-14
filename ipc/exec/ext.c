#include <stdio.h>

void main(){
	printf("main.pid: %d\n", getpid());
	system("./test");
}
