#include <stdio.h>
#include <fcntl.h>

int main(){
	int fd = open("./1.txt",O_CREAT | O_RDONLY,0600);
	sleep(3);
	close(fd);
}
