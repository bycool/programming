#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>

#include "bb.h"

int eflag = 0;

void kill_process(int signo){
    printf("ctrl+c\n");
    eflag = 1;
}


void main(){
	char* ctrlfile = "/mnt/debugfs/bbctrl0";
	char* datafile = "/mnt/debugfs/bbdata0";
	char* rule1 = "11,/dev/sdb";
	char* rule2 = "12,/dev/sdc";
	char* rule3 = "13,/dev/sdc";
	char* rule4 = "13,/dev/sda3";
	char* rule0 = "2,";
	int ret = 0;
	char* cread = "3";
	unsigned char* data = 0;
	void* mapdata = NULL;
	int ready_cnt = 0;
	char rbio[64];

	signal(SIGINT, kill_process);

	int fc = open(ctrlfile, O_RDWR, 0600);
	if(fc < 0) return ;
	write(fc, rule1, strlen(rule1));
	write(fc, rule2, strlen(rule2));
	write(fc, rule3, strlen(rule3));
	write(fc, rule4, strlen(rule4));
	write(fc, rule0, strlen(rule0));

//	write(fc, "3", 1);
//	ret = read(fc, "3", 1);
//	printf("ret = : %d\n", ret);
//
	int fd = open(datafile, O_RDONLY, 0600);
	if(fc < 0) { close(fc);  return ; }

	mapdata = mmap(NULL, BB_DATA_RELAY_BUFSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(mapdata == MAP_FAILED) {
		printf("mmap fail\n");
		close(fd);
		close(fc);
		return ;
	}

	data = mapdata;
	printf("data = mapdata\n");
	while(!eflag){
		if(read(fc, "3", 1)==0){
			sleep(1);
			continue;
		}
		if(data == mapdata+BB_DATA_RELAY_BUFSIZE){
			printf("restart map start\n");
			data = mapdata;
		}

		strcpy(rbio, data);
		printf("rbio: %s", rbio);
		data += 64;

		write(fc, "3", 1);
	}
	
	

	if(mapdata){
		munmap(mapdata, BB_DATA_RELAY_BUFSIZE);
		printf("munmap (data relay)\n");
	}

	close(fd);
	close(fc);
}
