#include <sys/time.h>

int main(){
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	printf("%d, %d\n",tv.tv_sec, 100000 + tv.tv_usec);
}

