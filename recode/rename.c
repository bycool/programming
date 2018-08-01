#include <stdio.h>
#include <fcntl.h>
int main(){
	int fd = -1;
	fd = open("./test/2011/11/2/43.txt", O_WRONLY | O_APPEND, 0600);
	rename("test/2011/11/2/43.txt","test/2011/11/2/43.txt.rename");
	write(fd, "11111111", 10);
	close(fd);
}
