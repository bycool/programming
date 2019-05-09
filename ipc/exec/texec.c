#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void main(){
	
	pid_t pid = getpid();
	printf("pid:%d\n", pid);

	int i = 10;
	int ret_state = 0;

	pid = fork();
	if(pid == 0){
		execve("./test", NULL, NULL );
		exit(10);
	}else if(pid >0){
		waitpid(pid, &ret_state, 0);
		while(i--){
			printf("main\n");
			sleep(1);
		}
	}
}
