#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

char buf[50000];

int riomain(){
	int ntow,nw;
	char *ptr;
	ntow = read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr,"read %d bytes.\n",ntow);

	int flags = fcntl(STDOUT_FILENO,F_GETFL,0);
	fcntl(STDIN_FILENO,F_SETFL,flags|O_NONBLOCK);

	ptr = buf;
	while(ntow > 0) {
		errno = 0;
		nw = write(STDOUT_FILENO,ptr,ntow);
		fprintf(stderr,"nwrite = %d, error = %d\n",nw,errno);

		if(nw > 0) {
			ptr += nw;
			ntow -= nw;
		}
	}
	fcntl(STDOUT_FILENO,F_SETFL,flags|~O_NONBLOCK);

}

int main(){
	riomain();
}
