#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	struct stat fdst;
	int rc = stat("1", &fdst);
	printf("st_ino: %lu\nst_mode: %x\n",fdst.st_ino, fdst.st_mode);

	if(S_ISREG(fdst.st_mode)){
		printf("reg\n");
	}
}
