#include <stdio.h>
#include <fcntl.h>

int main(){
	char c = 0;
	int fd = open("./1.txt", O_RDONLY, 0600);
	read(fd, &c, 1);
	printf("%c\n",c);
	read(fd, &c, 1);
	printf("%c\n",c);
	read(fd, &c, 1);
	printf("%c\n",c);
	close(fd);
}
