#include <fcntl.h>
#include <stdio.h>

int main( int argc, char *argv[] ){
	
	int err = open("./file1.txt",O_RDWR);
	if(err == -1) { printf("cant open file1.txt\n");}

	open_usage();
}

int open_usage(){
#define fpe(s)	fprintf( stderr, s"\n")
	fpe( " Usage: open(filepath,flages)" );
	fpe( " ---------- " );
	fpe( " O_RDONLY : 只读打开" );
	fpe( " O_WRONLY : 只写打开" );
	fpe( " O_RDWR   : 读写打开" );
	fpe( " ---------- " );
	fpe( " O_APPEND : 追加打开，每次写时都追加到文件尾" );
	fpe( " O_CREAT  : 文件不存在，则创建，还需要一个文件权限参数" );
	fpe( " O_EXCL   : 与O_CREAT同用，用来测试文件是否已经存在，可防止o_creat时报错，与o_create合为原子操作" );
	fpe( " ----------" );
}
