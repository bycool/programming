#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char buf[64] = {0};
	struct timeval tv;
	struct timezone tz;

	struct stat fdst;

	gettimeofday(&tv,&tz);

	printf("%d\n",tv.tv_sec);
	printf("%d\n",tv.tv_usec);

	sprintf(buf, "[%d%d]",tv.tv_sec, tv.tv_usec);

	printf("%s\n", buf);

	printf("-------------\n");
	int fd = open("1.txt", O_CREAT|O_WRONLY|O_APPEND,0600);
	write(fd,"1\n",2);
	close(fd);

	stat("1.txt", &fdst);
	printf("%lu\n", fdst.st_mtime);
	

}
