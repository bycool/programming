#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void main(){
	int rc = chdir("/tmp");
	if(rc == 0){
		rc = open("./jjd", O_CREAT | O_WRONLY, 0600);
		write(rc, "hello", 5);
		close(rc);
	}
}
