#include <stdio.h>
#include <fcntl.h>

int main(){
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 1;
	lock.l_len = 1;
	lock.l_pid = -1;

	int fd = open("./1.txt",O_CREAT | O_RDWR , 0600);
	int rc = fcntl(fd,F_SETLKW,&lock);
	if(rc<0){
		printf("lock 1.txt.offset.1 read fail\n");
	}
	//remove("./1.txt");
	close(fd);
}
