#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
void main()
{
	int fd = open("./1.txt", O_CREAT | O_WRONLY, 0600);
    struct timeval t1,t2;
    double timeuse;
    gettimeofday(&t1,NULL);
    write(fd, "1",1);
    gettimeofday(&t2,NULL);
	close(fd);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("Use Time:%f\n",timeuse);
}
