#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(){
	char buf[3] = "./";
	DIR *pdir = NULL;
	struct dirent *pdirent = NULL;
	pdir = opendir(buf);
//	pdirent = readdir(pdir);
	while((pdirent=readdir(pdir))!=NULL){
		if(strcmp(pdirent->d_name,"1")==0)
			rename("1", "1.rename");
		printf("%s\n",pdirent->d_name);
	}
	return 0;
}
