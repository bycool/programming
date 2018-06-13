#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
/*
	int fd = open("1", O_RDWR , 0600);
	ftruncate(fd,3);
	close(fd);
*/

	truncate("1", 3);
	
}
