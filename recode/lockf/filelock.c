#include <stdio.h>
#include <fcntl.h>

int main(){
	struct flock lock;
	int fd = open("./1.txt",O_CREAT | O_WRONLY,0600);
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 1;
	lock.l_pid = -1;
	int rc = fcntl(fd,F_SETLKW,&lock); //lock 0
//	lock.l_type = F_UNLCK;
	lock.l_start = 1;
	fcntl(fd,F_SETLKW,&lock);  //lock 1
/*	fd = open("./1.txt",O_CREAT | O_WRONLY, 0600);
	write(fd, "2",1);
	printf("write 1 to 1.txt\n");
*/
	printf("sleep 5\n");
	sleep(5);
	close(fd);
	return 0;
}
