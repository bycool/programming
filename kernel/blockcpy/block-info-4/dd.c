#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char * blkinfo0 = "/mnt/debugfs/blkinfo0";
char * sdb1 = "/dev/sdb1";
char * outb = "./ob";
char * sdc1 = "/dev/sdc1";

void main(){
	int n = 0;
	char buf[1024] = {0};

	int fdb = open(sdb1, O_RDONLY, 0600);
//	int oub = open(outb, O_WRONLY | O_CREAT | O_EXCL, 0600);
	int fdc = open(sdc1, O_WRONLY, 0600);
	while(read(fdb, buf, 1024)!=0){
		write(fdc, buf, 1024);
	}
	close(fdb);
	close(fdc);
}
