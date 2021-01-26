#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void main(){
	char* ctrlfile = "/mnt/debugfs/bbctrl0";
	char* rule1 = "11,/dev/sdb1";
	char* rule2 = "12,/dev/sdc1";
	char* rule3 = "2,";

	int fd = open(ctrlfile, O_WRONLY, 0600);
	if(fd < 0) return ;

	write(fd, rule1, strlen(rule1));
	write(fd, rule2, strlen(rule2));
	write(fd, rule3, strlen(rule3));
	close(fd);
}
