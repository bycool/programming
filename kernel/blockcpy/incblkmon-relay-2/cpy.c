#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

char* ifile = "/dev/sdb1";
char* ofile = "/dev/sdc1";
char* blockinfo = "/mnt/debugfs/blockinfo0";

char buf[32] = {0};
char cpybuf[1024] = {0};

int exit_flag = 0;
void kill_process(int signo){
	printf("ctrl+c\n");
	exit_flag = 1;
}

void main(){
	char *ps = NULL, *pl = NULL;
	int sta, len;
	char* ret = NULL;
	off_t offset = 0;
	signal(SIGINT, kill_process);
	FILE *fp= fopen(blockinfo, "r");
	int fdb = open(ifile, O_RDONLY);
	int fdc = open(ofile, O_WRONLY);
	if(!fp) { printf("open block info fail\n"); return ; }
	while(!exit_flag){
		ret = fgets(buf, 32, fp);
		if(ret != buf){ sleep(2); continue; }
		printf("%s", buf);
		ps = buf;
		pl = strchr(ps, ',');
		if(pl) *pl++=0;
		sta = atoi(ps) * 512;
		len = atoi(pl);
		printf("write:start: %d, len: %d\n", sta, len);
		lseek(fdb, sta, SEEK_SET);
		lseek(fdc, sta, SEEK_SET);
		read(fdb, buf, 1024);
		write(fdc, buf, 1024);
	}
	fclose(fp);
	close(fdb);
	close(fdc);
}
