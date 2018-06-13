#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>

int main(){
	char base[512] = {0};
	DIR* pdir = NULL;
	struct dirent *pdirent;

	pdir = opendir("./test");
	printf("opendir\n");
	while(NULL!=(pdirent = readdir(pdir))){
		sleep(1);
		printf("name: %s\n",pdirent->d_name);
	}
	
}
