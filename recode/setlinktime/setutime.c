#include <stdio.h>
#include <sys/time.h>
#include <utime.h>

int main(){
	int rc = 0;
	struct timeval tvl;
	struct timezone tze;

	gettimeofday(&tvl, &tze);

	struct utimbuf timebuf;
	timebuf.actime = (time_t)tvl.tv_sec;
	timebuf.modtime = (time_t)tvl.tv_sec;

	rc = utime("./1.txt.link", &timebuf);
	if(rc){
		printf("error\n");
		return -1;
	}
	printf("ok\n");
	return 0;
}
