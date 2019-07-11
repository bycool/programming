#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(){
	int fd = open("ttt.txt", O_CREAT|O_WRONLY, 0600);
	if(fd<0)
		printf("write error: %d, %s\n",errno, strerror(errno));
	lseek(fd, 3, SEEK_SET);
	write(fd, "4", 1);
	lseek(fd, 0, SEEK_SET);
	write(fd, "123", 3);
	close(fd);
}
