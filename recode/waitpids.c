#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void main(){
	int pid = 0;
	int ppid = 0;
	if((pid = fork()) == 0){
		printf("child1: %d\n", getpid());
		sleep(10);
		printf("child1: exit child1\n");
		exit(0);
	}else if(pid > 0){
		if((ppid = fork()) == 0){
			printf("child2: %d\n", getpid());
			sleep(5);
			printf("child2: exit child2\n");
		}else if(ppid > 0){
			int status = -1;
			wait(&status);
			printf("parent: %d\n", getpid());
			sleep(2);
			printf("parent: exit parent\n");
		}
	}
}
