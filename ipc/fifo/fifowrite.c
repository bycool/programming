#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

#define BUF_SIZE 256

int main(){
	char buf[BUF_SIZE];
	int fd;
	int i;

	unlink("myfifo");

	if(mkfifo("myfifo",0666)<0){
		printf("create fifo error\n");
		exit(1);
	}

	fd = open("myfifo",O_WRONLY);
	if(fd<0){
		printf("open fifo error\n");
		exit(1);
	}
	printf("open fifo success\n");

	for(i=0;i<10;i++){
		bzero(buf,BUF_SIZE);
		int len = sprintf(buf,"write fifo : %d",i);
		if(write(fd,buf,len)<0){
			printf("write fifo error\n");
			close(fd);
			exit(1);
		}
		printf("write fifo: %s\n",buf);
		sleep(1);
	}
	close(fd);
}

