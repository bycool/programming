#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>


int main(){
	int fd = open("/mnt/debugfs/relay_test_dir/cpu0",O_RDWR,770);
	char buf[31];
	int rc = 0;
	int r=1000000;
	do{
		rc = read(fd,buf,31);
		if(rc<=0) usleep(10000);
		buf[rc] = 0;
		//printf("rc: %d : buf: %s\n", rc ,buf);
		printf("%s", buf);
		
	}while(1);

	return 0;
}

