#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
	char buf[32] = "";
	int file_type = 1;
	sprintf(buf, "\t<ora_type>%d</ora_type>", file_type);
	printf("%s\n", buf);
	int fd = open("fzs.xml", O_CREAT|O_WRONLY, 0600);
	write(fd, buf, strlen(buf));
	close(fd);
	return 0;
}

