#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 512

int main(){
	int fd;
	char buf[BUF_SIZE];
	int len;

	fd = open("myfifo",O_RDONLY);
	if(fd<0){
		printf("open fifo error\n");
		exit(1);
	}
	printf("open fifo success\n");

	bzero(buf,BUF_SIZE);
	while((len=read(fd,buf,BUF_SIZE))>0){
		printf("read from fifo: %s\n",buf);
	}
	close(fd);
}
