#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main(){
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	if(pipe(fd)<0) printf("pipe error\n");
	if((pid=fork())<0) printf("fork error\n");
	else if(pid>0){ //parent pid
		close(fd[0]);
		write(fd[1],"hello world\n",12);
	}else{	//children pid
		close(fd[1]);
		n = read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO,line,n);
	}
	exit(0);
}

