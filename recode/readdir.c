#include <stdio.h>
#include <dirent.h>

int main(){
	char buf[3] = "./";
	DIR *pdir = NULL;
	struct dirent *pdirent = NULL;
	pdir = opendir(buf);
//	pdirent = readdir(pdir);
	while((pdirent=readdir(pdir))!=NULL)
		printf("%s\n",pdirent->d_name);
	return 0;
}
