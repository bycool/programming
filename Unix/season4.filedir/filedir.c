#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define fpe(s)    fprintf( stderr, s"\n")
void raccess();
void rumask();

int main(int argc, char *argv[]){
	int ret;
	while(-1 != ( c = getopt(argc, argv,"r:h:")) ){
		switch(ret){
			case 'r':
			
		}
	}
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
	fpe(" ---------------------------------------")
}

void rumask(){
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH )
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


















