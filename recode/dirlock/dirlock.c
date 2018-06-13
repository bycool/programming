#include <stdio.h>
#include <fcntl.h>

int main(){
	struct flock lock;
	int fd = open("./tmp",O_RDONLY,0600);
	lock.l_type = 
}

