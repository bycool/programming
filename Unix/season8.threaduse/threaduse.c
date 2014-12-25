#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void rfork();
void rvfork();

main(){
//	rfork();
	rvfork();
}

void rfork(void){
	int ret;
	ret = fork();
	printf("ret = %d\n",ret);
	if(ret == 0){
		printf("ret == 0 %d, %d\n",getpid(),getppid());
	}	
	if(ret > 0){
		printf("ret > 0 %d, %d\n",getpid(),getppid());
	}
}
void rvfork(void){
	int ret;
	if((ret = vfork())<0){
		printf("vfork error\n");
	}else if(ret == 0){
		printf("children\n");
		exit(0);
	}
	printf("parent\n");
}


