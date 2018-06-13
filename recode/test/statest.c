#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	struct stat fdst;
	int rc = stat("1", &fdst);
	if(rc == 0)
		printf("1\n");
	else
		perror("1");
}
