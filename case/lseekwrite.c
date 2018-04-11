#include <stdio.h>
#include <fcntl.h>


int main(){
	int fd,ret;
	fd = open("./lseek.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
	write(fd,"lseek",5);
	close(fd);
	fd = open("./lseek.txt",O_WRONLY);
	ret = lseek(fd,5,SEEK_END);
	if(ret!=-1)
		write(fd,"write",5);
	ret = lseek(fd,0,SEEK_END);
	if(ret!=-1)
		write(fd,"lseek",5);
	ret = lseek(fd,5,SEEK_SET);
	if(ret!=-1)
		write(fd,"write",5);
	close(fd);
}
