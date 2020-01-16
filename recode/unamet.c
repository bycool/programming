#include <sys/utsname.h>
#include <stdio.h>

void main(){
	struct utsname buf;
	printf("%s\n", buf);
	if(uname(&buf))
		printf("uname err\n");
	printf("sysname: %s\n", buf.sysname);
	printf("nodename: %s\n", buf.nodename);
	printf("release: %s\n", buf.release);
	printf("version: %s\n", buf.version);
	printf("machine: %s\n", buf.machine);
}
