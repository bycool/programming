#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void rfork();
void rvfork();
void rwait();
void rexec();

main(){
//	rfork();
//	rvfork();
	rwait();
}

void rfork(void){
	int ret;
	ret = fork();
	printf("ret = %d\n",ret);
	if(ret == 0){
//		printf("ret == 0 %d, %d\n",getpid(),getppid());
	exit(0);
	}	
	if(ret > 0){
//		printf("ret > 0 %d, %d\n",getpid(),getppid());
	}
	printf("after all %d\n",getpid());
	
	/**
	子进程不只在if{}内有要执行的代码，如果在pid==0的{}里不使用exit退出，则子进程也不执行父进程的代码，因为子进程复制了这个父进程，代码段是相同的。但是其他字段就不共享。
	**/
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


void rwait(){
	int ret;
	if( (ret = fork())<0 ){
		printf("err fork \n");
	}else if(ret == 0 ){ //child
		printf("child sleep 5s\n");
		sleep(5);
	}else{	//parent
		printf("parent waiting ...\n");
		wait(ret);
		printf("parent exit\n");
	}

	
}

void rexec(){
	int ret;
	if
}


























