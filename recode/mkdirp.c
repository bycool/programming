#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

void mkdirp(char* path){
    char* st = NULL;
    char* en = NULL;

    if(!path){
        printf("path is null\n");
        return ;
    }

    st = path;
    en = path ;

    while((en=strchr(en+1, '/')) != NULL){
        *en = '\0';
        if(access(st, F_OK) == 0){
            *en = '/';
            continue;
        }else{
            if(mkdir(st, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0){
                perror(st);
            }
            *en = '/';
        }
    }
}


void move_file_to_outdir(char* filename, char* outdir){
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

    mkdirp(path);

}


int main(int argc, char* argv[]){

	char outdir[64] = "/home/ten/source/test/";
	char filename[128] = "/home/ten/source/test/tsext/sdfs/wefsd/w/e/fs/df/we/fs/t1.txt";

	move_file_to_outdir(filename,outdir);
}
