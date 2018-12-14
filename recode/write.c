#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd = open("ttt.txt", O_CREAT|O_WRONLY, 0600);
	lseek(fd, 3, SEEK_SET);
	write(fd, "4", 1);
	lseek(fd, 0, SEEK_SET);
	write(fd, "123", 3);
	close(fd);
}
