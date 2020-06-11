#include <stdio.h>
#include <fcntl.h>

int main(){
	char c;
	int fd = open("1", O_RDONLY, 0600);
//	read(fd, &c, 1);
	getchar();
	close(fd);
	printf("%c\n",c);
}
