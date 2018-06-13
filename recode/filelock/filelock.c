#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 1;
	lock.l_type = F_WRLCK;
	lock.l_pid = -1;

	int fd = open("./1.txt",O_CREAT|O_RDWR,0666);
	int ret = fcntl(fd,F_SETLKW,&lock);
	if(ret<0)
		printf("set lock error\n");
	char buf[2] = {0};
	read(fd,buf,1);
	buf[1]=0;
	printf("%s, pid:%d\n",buf,getpid());
	sleep(10);

//	lock.l_type = F_UNLCK;
//	ret = fcntl(fd,F_SETLKW,&lock);
//	if(ret<0)
//		printf("unlock error\n");

	close(fd);

    getchar();

	return 0;
}

