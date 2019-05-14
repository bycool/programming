#include <stdio.h>

void main(int argc, char* argv[]){
	int i = 30;
	int p = 1;
	printf("test.pid: %d\n", getpid());
	while(i--){
	//	for(p=1; p<argc; p++)
	//	  printf("%s ", argv[p]);

		printf("hello world\n");
		sleep(2);
	}
}
