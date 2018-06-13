#include <stdio.h>
#include <fcntl.h>

int main(){
	char buf[20] = "";
	int fd = open("33", O_CREAT | O_WRONLY, 0600);
	write(fd, "1111111111", 10);
	close(fd);
	fd = open("33", O_RDONLY, 0600);
	rename("33", "33.tex");
	read(fd, buf, 20);
	printf("%s\n", buf);
	close(fd);
}
