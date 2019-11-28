#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(){
	int fd = open("/home/ten/t1/222222/ttt.txt", O_CREAT|O_WRONLY, 0600);
	if(fd<0)
		printf("write error: %d, %s\n",errno, strerror(errno));
	write(fd, "4", 1);
	write(fd, "123", 3);
	close(fd);
}
