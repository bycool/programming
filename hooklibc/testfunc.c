#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(){
	creat("1.txt", 0600);
	int fd = open("1.txt", O_CREAT | O_WRONLY | O_APPEND, 0600);
	write(fd, "123456", 6);
	close(fd);
	//rename("1.txt", "2.txt");
}
