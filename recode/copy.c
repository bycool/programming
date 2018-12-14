#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <utime.h>
#include <zlib.h>
#include <semaphore.h>



void copy_to_outdir(char* srcdir, char* outdir){
	int rc = -1;
    FILE* srcfp = NULL;
    FILE* tarfp = NULL;
    DIR* readir = NULL;
    struct dirent* pdirent = NULL;
    struct stat tst;
	char srcpath[4096] = {0};
    char tarpath[4096] = {0};
    char readbuf[4096] = {0};
    readir = opendir(srcdir);
    while((pdirent=readdir(readir))!=NULL){
        if(strcmp(pdirent->d_name,".")==0 || strcmp(pdirent->d_name,"..")==0){
            continue;
        }

		sprintf(srcpath, "%s%s", srcdir, pdirent->d_name);
        sprintf(tarpath, "%s%s", outdir, pdirent->d_name);

        stat(srcpath, &tst);
        if(!S_ISDIR(tst.st_mode)){
            srcfp = fopen(srcpath,"r");
            tarfp = fopen(tarpath, "w+");
            while(!feof(srcfp)){
                rc = fread(readbuf, 1, sizeof(readbuf), srcfp);
				printf("sizeof(readbuf): %d, rc: %d\n", sizeof(readbuf), rc);
                fwrite(readbuf, rc, 1, tarfp);
            }
            fclose(srcfp);
            fclose(tarfp);
        }else{
			rc = strlen(tarpath);
			if(tarpath[rc-1] != '/')
				tarpath[rc] = '/';
			rc = strlen(srcpath);
			if(srcpath[rc-1] != '/')
				srcpath[rc] = '/';
            mkdir(tarpath, tst.st_mode);
			copy_to_outdir(srcpath, tarpath);
        }
    }
}


int main(){
	char srcdir[64] = "/home/ten/sjslog/";
	char tardir[64] = "/home/ten/tmp/";

	copy_to_outdir(srcdir, tardir);

	
}
