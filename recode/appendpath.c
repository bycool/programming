#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void appendpath(char* outdir, char* filename){
	int rc = -1;
	struct stat fst;
	char* tmpfilename = NULL;
	char* p = NULL;
	char path[4096] = {0};

	if(!outdir){
		printf("outdir is null\n");
		return ;
	}
	if(!filename || filename[0]!='/'){
		printf("filename null or wrong\n");
		return ;
	}
	rc = stat(outdir, &fst);
	if(rc != 0){
		printf("stat(%s} error\n", outdir);
		return ;
	}
	if(!S_ISDIR(fst.st_mode)){
		printf("%s Not Dir\n", outdir);
		return ;
	}

	p = filename;
	rc = strlen(outdir);
	if(outdir[rc-1] != '/'){
		tmpfilename = filename;
	}else{
		tmpfilename = p + 1;
	}

	sprintf(path, "%s%s", outdir, tmpfilename);

	rc = strlen(path);
	if(path[rc] != '/'){
		while(path[rc] != '/'){
			path[rc] = '\0';
			rc--;
		}
	}

}

in main(){
	char outdir[64] = "/home/ten/source/";
	char filename[32] = "/home/ten/1.txt";
	appendpath(outdir, filename);
}
