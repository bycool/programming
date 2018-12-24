#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE 256

int main(){
	int fd[2];
	char data[] = "hello i am parent";
	char buf[BUF_SIZE];

	pid_t pid;

	if(pipe(fd)<0){
		printf("pipe error\n");
		exit(1);
	}

	pid = fork();
	if(pid<0){
		printf("fork() error\n");
		exit(1);
	}else if(pid==0){
		close(fd[1]);
		int len = read(fd[0],buf,sizeof(buf));
		printf("child: %s\n",buf);
	}else{
		close(fd[0]);
		write(fd[1],data,strlen(data));
//		printf("parent: %s\n",data);
		read(fd[0],buf,sizeof(buf));
		sleep(1);
	}

}
