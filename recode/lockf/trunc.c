#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd = open("./1.txt",O_RDWR|O_TRUNC);
	close(fd);
}

