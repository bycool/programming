#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){
	int fd = open("1.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
	write(fd, "123456", 6);
	close(fd);
}
