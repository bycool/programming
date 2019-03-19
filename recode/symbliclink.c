#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    char buf[3] = "./";
    DIR *pdir = NULL;
    struct dirent *pdirent = NULL;
	struct stat st;
    pdir = opendir(buf);
//    pdirent = readdir(pdir);
    while((pdirent=readdir(pdir))!=NULL){
        if(strcmp(pdirent->d_name,".") == 0 || strcmp(pdirent->d_name, "..")==0)
			continue;

		if(lstat(pdirent->d_name, &st))
			continue;

	    if(S_ISLNK(st.st_mode))
	        printf("%s\n",pdirent->d_name);
    }
    return 0;
}

