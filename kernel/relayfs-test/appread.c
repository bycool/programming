#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>


int main(){
	int fd = open("/mnt/debugfs/relay_test_dir/cpu0",O_RDWR,770);
	char buf[31];
	int r=0;
	do{
		sleep(1);
		r = read(fd,buf,10);
		printf("%s\n",buf);
	}while(r>0);

	return 0;
}

