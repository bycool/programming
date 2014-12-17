#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main( int argc, char *argv[] ){
	int err;
	int c;
	int ret;
	while(-1 != (ret = getopt(argc,argv,"r:h:")) ){
		switch(ret) {
			case 'r' :
				printf("The argument of -b is %s\n",optarg);
	
				if( strcmp("open",optarg) == 0 )   c = '1';  else
				if( strcmp("create",optarg) == 0 ) c = '2';  else
				if( strcmp("close",optarg) == 0 )  c = '3';  else
				if( strcmp("lseek",optarg) == 0 )  c = '4';  else
				if( strcmp("read",optarg) == 0 )   c = '5';  else
				if( strcmp("write",optarg) == 0 )  c = '6';
				

				switch(c) {
					case '1' : //r:open
						printf("R:open\n");
						int err = open("./file1.txt",O_RDWR);
						if(err == -1) printf("cant open file1.txt\n");
						break;
					case '2' : //r:create
						printf("R:create\n");
						break;
					case '3' : //r:close
						printf("R:close\n");
						break;
					case '4' : //r:lseek
						printf("R:lseek\n");
						break;
					case '5' : //r:read
						printf("R:read\n");
						break;
					case '6' : //r:write
						printf("R:write\n");
						break;
					default :
						printf("R:err::the argumetn is not included in {open,create,close,lseek,read,write}\n");
						break;
					
				}//endl-switch(optarg)				
				break;

			case 'h' :
				printf("The argument of -b is %s\n\n",optarg);

				if( strcmp("open",optarg) == 0 )   c = '1';  else
				if( strcmp("create",optarg) == 0 ) c = '2';  else
				if( strcmp("close",optarg) == 0 )  c = '3';  else
				if( strcmp("lseek",optarg) == 0 )  c = '4';  else
				if( strcmp("read",optarg) == 0 )   c = '5';  else
				if( strcmp("write",optarg) == 0 )  c = '6';

					case '1' : //h:open
						printf("H:open\n");
						int err = open("./file1.txt",O_RDWR);
						if(err == -1) printf("cant open file1.txt\n");
						break;
					case '2' : //h:create
						printf("H:create\n");
						break;
					case '3' : //h:close
						printf("H:close\n");
						break;
					case '4' : //h:lseek
						printf("H:lseek\n");
						break;
					case '5' : //h:read
						printf("H:read\n");
						break;
					case '6' : //h:write
						printf("H:write\n");
						break;
					default :
						printf("H:err::the argumetn is not included in {open,create,close,lseek,read,write}\n");
						break;
				break;				

			default:
				break;
		} //endl-switch(ret)
		

	} //endl-while(getopt)

}//endl-main

int open_usage(){
#define fpe(s)	fprintf( stderr, s"\n")
	fpe( " Usage: open(filepath,flages) headfile: fcntl.h " );
	fpe( " ---------- " );
	fpe( " O_RDONLY : 只读打开" );
	fpe( " O_WRONLY : 只写打开" );
	fpe( " O_RDWR   : 读写打开" );
	fpe( " ---------- " );
	fpe( " O_APPEND : 追加打开，每次写时都追加到文件尾" );
	fpe( " O_CREAT  : 文件不存在，则创建，还需要一个文件权限参数" );
	fpe( " O_EXCL   : 与O_CREAT同用，用来测试文件是否已经存在，可防止o_creat时报错，与o_create合为原子操作" );
	fpe( " ----------" );

} //end-open_usage
