#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd = open("2",O_CREAT | O_WRONLY, 0600);
	write(fd, "1", 1);
	write(fd, "2", 2);
	close(fd);
}
