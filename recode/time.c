#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(){
	char buf[64] = {0};
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv,&tz);

	printf("%d\n",tv.tv_sec);
	printf("%d\n",tv.tv_usec);

	sprintf(buf, "[%d%d]",tv.tv_sec, tv.tv_usec);

	printf("%s\n", buf);

}
