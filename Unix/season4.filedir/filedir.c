#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define fpe(s)    fprintf( stderr, s"\n")
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH )

void raccess();
void rumask();
void access_usage();
void umask_usage();
void filedir_usage();
void rchmod();

int main(int argc, char *argv[]){
	int ret;
	int c;
	while(-1 != ( ret = getopt(argc, argv,"r:h:")) ){
		if( strcmp("access",optarg) == 0 ) c = '1';	else
		if( strcmp("umask",optarg ) == 0 ) c = '2'; else
		if( strcmp("chmod",optarg ) == 0 ) c = '3'; else
		if( strcmp("stat" ,optarg ) == 0 ) c = '4';
		switch(ret){
			case 'r' :
				switch(c){
					case '1' : //r:access
						printf("r:access\n");
						raccess();
						break;
					case '2' : //r:umask
						printf("r:umask\n");
						rumask();
						break;
					case '3' : //r:chmod/fchmod
						rchmod();
						break;
					case '4' : //r:stat/fstat/lstat
						rstat();
						break;
					default :
						filedir_usage();
						break;
				}
				break;
			case 'h' :
				switch(c){
					case '1' : //h:access
						printf("h:access\n");
						access_usage();
						break;
					case '2' : //h:umask
						printf("h:umask\n");
						umask_usage();
						break;
					case '3' : //h:chmod/fchmod
						chmod_usage();
						break;
					case '4' : //h:stat/fstat/lstat
						stat_usage();
						break;
					default  :
						filedir_usage();
						break;
				}
				break;
			default  :
				filedir_usage();
				break;
			
		}
	}
}

void filedir_usage(){
	fpe(" Usage : filedir_usage");
	fpe(" ------------------------");
	fpe(" main -r {access,umask}");
	fpe("      -h {access,umask}");
	fpe(" ------------------------");	
}

void raccess(){
	int fd = open("./access.txt",O_RDWR | O_CREAT | O_EXCL , S_IRUSR);
	close(fd);
	int ret = access("./access.txt",R_OK);	//测试读权限
	if( 0 == ret ) printf("file access.txt test R_OK is %d\n",ret);
	ret = access("./access.txt",W_OK);		//测试写权限
	if( 0 == ret ) printf("file access.txt test W_OK is %d\n",ret);
	ret = access("./access.txt",X_OK);		//测试执行权限
	if( 0 == ret ) printf("file access.txt test X_OK is %d\n",ret);
	ret = access("./access.txt",F_OK);		//测试文件是否存在
	if( 0 == ret ) printf("file access.txt test F_OK is %d\n",ret);
}
void access_usage(){
	fpe(" Usage : access(const char*, int)");
	fpe(" ---------------------------------------");
	fpe(" #include <unistd.h>");
	fpe(" int access(const char* pathname, int mode);");
	fpe(" --mode------------");
	fpe(" R_OK:测试读权限");
	fpe(" W_OK:测试写权限");
	fpe(" X_OK:测试执行权限");
	fpe(" F_OK:测试文件是否存在");
	fpe(" ---------------------------------------");
}

void rumask(){
	umask(0);
	if( creat("./umask1.txt",RWRWRW) < 0 ) printf("creat error for umask1.txt");
	umask( S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
	if( creat("./umask2.txt",RWRWRW) < 0 ) printf("creat error for umask2.txt");
}
void umask_usage(){
	fpe(" Usage : umask(mode_t cmask)");
	fpe(" ----------------------------------------");
	fpe(" #include <sys/stat.h>");
	fpe(" mode_t umask(mode_t cmask)");
	fpe(" ----------------------------------------");
	fpe(" umask函数为进程设置文件模式创建屏蔽字，并返回以前的值");
}

void rstat(){
    int ret;
    if( creat("./stat.txt",RWRWRW) < 0 ) printf("creat error for stat.txt");
    struct stat buf;
    ret = stat("./stat.txt", &buf);
    if(ret != 0) printf("err :: cant get stat from stat.txt\n");
    printf("./stat.txt.mode_t = %d\n",buf.st_mode);

}
void stat_usage(){
	fpe(" Usage : stat(const char*, struct stat* )");
	fpe(" ----------------------------------------");
	fpe(" #include <sys/stat.h>");
	fpe(" int stat(const char *restrict pathname, struct stat *restrict buf)");
	fpe(" ----------------------------------------");
	fpe(" 一旦给出pathname,stat函数就返回与命名文件相关的信息结构提");
	fpe(" ----------------------------------------");
}

void rchmod(){
	struct stat buf;
	if( creat("./chmod.txt",RWRWRW) < 0 ) printf("creat error for chmod.txt");
	int ret = stat("./chmod.txt",&buf);
	if( ret != 0 ) printf("err :: cant get stat from chmod.txt\n");
	printf("./chmod.txt.mode_t = %d\n",buf.st_mode);
	if( chmod("./chmod.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) < 0 ) printf("cant chmod chmod.txt\n");
	if( stat("./chmod.txt",&buf) < 0 ) printf("err :: cant get stat from chmod.txt\n");
	printf("./chmod.txt.mode_t = %d\n",buf.st_mode);
	
}
void chmod_usage(){
	fpe(" Usage : chmod(const char*, mode_t)");
	fpe(" ---------------------------------------");
	fpe(" #include <sys/stat.h>");
	fpe(" int chmod(const char* pathname,mode_t mode)");
	fpe(" ---------------------------------------");
	fpe(" 更改现有文件权限");
}















