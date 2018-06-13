#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd = open("./1.txt",O_RDWR,0600);
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 1;
	lock.l_type = F_RDLCK;
	lock.l_pid = -1;
	if(-1==fcntl(fd,F_SETLKW,&lock)){
		printf("set read lock error\n");
	}
	char buf[2] = {0};
	lseek(fd,0,SEEK_SET);
	read(fd,buf,1);
	printf("buf:%s\n",buf);
	close(fd);
	
}

