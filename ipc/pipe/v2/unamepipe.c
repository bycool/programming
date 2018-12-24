#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int fd[2];

	if(pipe(fd)<0){
		printf("pipe() fail\n");
		return -1;
	}
	pid = fork();
	if(pid<0){
		printf("fork fail\n");
		return -1;
	}

	if(pid > 0){
		close(fd[1]);
		printf("father send to son: pid: %d\n", getpid());
		write(fd[0], "Hi son, i am ur father", 23);
		close(fd[0]);
	}

	if(pid == 0){
		close(fd[0]);
		char buf[32];
		printf("son read \n");
		int rc = read(fd[1], buf, sizeof(buf));
		printf("son: buf: %s\n", buf);
		close(fd[1]);
	}
}
