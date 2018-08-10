#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd = -1;
	char buf[20] = {"1234567890111213"};
	char* p = buf+2;
	printf("%s\n",p);
	fd = open("./1.txt", O_CREAT | O_WRONLY, 0600);
	write(fd, p, strlen(p));
	close(fd);
}
