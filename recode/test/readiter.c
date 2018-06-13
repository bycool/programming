#include <stdio.h>
#include <fcntl.h>

int main(){
	char buf[2] ;
	int fd = open("1",O_RDONLY,0600);
	read(fd,buf,1);
	buf[1] = 0;
	printf("%s\n",buf);
	read(fd,buf,1);
	buf[1] = 0;
	printf("%s\n",buf);
	close(fd);
}
