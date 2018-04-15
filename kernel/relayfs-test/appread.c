#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(){
	int fd = open("/mnt/debugfs/relay_test_dir/cpu0",O_RDWR,770);
	void* map_relay = mmap(NULL, 1024*1024, PROT_READ | PROT_WRITE,MAP_PRIVATE, fd,0);
	munmap(map_relay,1024*1024);
	return 0;
}

