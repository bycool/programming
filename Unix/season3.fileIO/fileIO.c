#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void open_usage();
void creat_usage();
void close_usage();
void lseek_usage();
void read_usage();
void write_usage();
void fcntl_usage();
void sync_usage();
void fileIO_usage();

int main( int argc, char *argv[] ){
	int err;
	int c;
	int ret;
	int fd;
	while(-1 != (ret = getopt(argc,argv,"r:h:")) ){
		switch(ret) {
			case 'r' :
				printf("The argument of -b is %s\n",optarg);
	
				if( strcmp("open",optarg) == 0 )   c = '1';  else
				if( strcmp("creat",optarg) == 0 )  c = '2';  else
				if( strcmp("close",optarg) == 0 )  c = '3';  else
				if( strcmp("lseek",optarg) == 0 )  c = '4';  else
				if( strcmp("read",optarg) == 0 )   c = '5';  else
				if( strcmp("write",optarg) == 0 )  c = '6';  else
				if( strcmp("fcntl",optarg) == 0 )  c = '7';  else
				if((strcmp("sync",optarg) & strcmp("fsync",optarg) & strcmp("fdatasync",optarg)) == 0) c = '8';
				

				switch(c) {
					case '1' : //r:open
						printf("R:open\n");
						fd = open("./open.txt",O_RDWR | O_CREAT | O_EXCL, S_IRWXU); //打开文件，不存在创建，设置权限 
						if( fd == -1) printf("cant open open.txt\n");
						write(fd,"open",4); //写open到文件
						close(fd); //关闭文件
						break;
					case '2' : //r:creat
						printf("R:create\n");
						err = creat("./create.txt",0777);
						if( err == -1 ) printf("cant create create.txt");
						fd = open("./create.txt",O_WRONLY);
						write(fd,"create",6);	
						close(fd);
						break;
					case '3' : //r:close
						printf("R:close\n");
						fd = open("./close.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
						write(fd,"close",5);
						close(fd);
						break;
					case '4' : //r:lseek
						printf("R:lseek\n");
						fd = open("./lseek.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
						write(fd,"lseek",5);
						close(fd);
						fd = open("./lseek.txt",O_RDWR);
						ret = lseek(fd,-4,SEEK_END);
						write(fd,"lseek",5);
						close(fd);
						break;
					case '5' : //r:read
						printf("R:read\n");
						char buf[10];
						fd = open("./read.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
						write(fd,"read",4);
						close(fd);
						fd = open("./read.txt",O_RDWR);
						ret = lseek(fd, -2, SEEK_END);
						read(fd,buf,10);
						printf("read from read.txt is %s\n",buf);
						close(fd);
						break;
					case '6' : //r:write
						printf("R:write\n");
						fd = open("./write.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
						write(fd,"write",5);
						close(fd);
						break;
					case '7' : //r:fcntl
						//fd = open("./fcntl.txt",O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
						//ret= fcntl(fd,F_GETFD); printf("current descriptor flags: %d\n",ret);
						//ret= fcntl(fd,F_SETFD,1);
						
						break;
					case '8' :

						break;
					default :
						printf("R:err::the argumetn is not included in {open,creat,close,lseek,read,write}\n");
						break;
					
				}//endl-switch(optarg)				
				break;

			case 'h' :
				printf("The argument of -b is %s\n\n",optarg);

				if( strcmp("open",optarg) == 0 )   c = '1';  else
				if( strcmp("creat",optarg) == 0 )  c = '2';  else
				if( strcmp("close",optarg) == 0 )  c = '3';  else
				if( strcmp("lseek",optarg) == 0 )  c = '4';  else
				if( strcmp("read",optarg) == 0 )   c = '5';  else
				if( strcmp("write",optarg) == 0 )  c = '6';  else
				if( strcmp("fcntl",optarg) == 0 )  c = '7';  else
				if((strcmp("sync",optarg) & strcmp("fsync",optarg) & strcmp("fdatasync",optarg)) == 0) c = '8';

				switch(c) {
					case '1' : //h:open
						open_usage();
						break;
					case '2' : //h:creat
						creat_usage();
						break;
					case '3' : //h:close
						close_usage();
						break;
					case '4' : //h:lseek
						lseek_usage();
						break;
					case '5' : //h:read
						read_usage();
						break;
					case '6' : //h:write
						write_usage();
						break;
					case '7' : //h:fcntl
						fcntl_usage();
						break;
					case '8' : //h:sync
						sync_usage();
						break;
					default : //-h 
						fileIO_usage();
						break;
				}			
				break;

			default: //-h
				fileIO_usage();
				break;
		} //endl-switch(ret)
		

	} //endl-while(getopt)

}//endl-main

#define fpe(s)	fprintf( stderr, s"\n")
void open_usage(){
	fpe( " Usage : open(const char*, int)");
	fpe( " ------------------------------------------ ");
	fpe( " #include <fcntl.h> ");
	fpe( " int open(const char *pathname, int flages) " );
	fpe( " ------------------------------------------ ");
	fpe( " --flages-- " );
	fpe( " O_RDONLY : 只读打开" );
	fpe( " O_WRONLY : 只写打开" );
	fpe( " O_RDWR   : 读写打开" );
	fpe( " O_APPEND : 追加打开，每次写时都追加到文件尾" );
	fpe( " O_CREAT  : 文件不存在，则创建，还需要一个文件权限参数" );
	fpe( " O_EXCL   : 与O_CREAT同用，用来测试文件是否已经存在，可防止o_creat时报错，与o_create合为原子操作" );
	fpe( " ----------" );
	fpe( " return: 成功返回文件描述符，失败返回-1 " );
	fpe( " ------------------------------------------ ");

} //end-open_usage

void creat_usage(){
	fpe( " Usage : creat(const char*, int)" );
	fpe( " ------------------------------------------ ");
	fpe( " #include <fcntl.h> ");
	fpe( " int creat(const char* pathname, mode_t mode) ");
	fpe( " ------------------------------------------ ");
	fpe( " ps:此函数等效: open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode) ");
	fpe( "    现在open函数提供了O_CREAT和O_TRUNC,于是不在需要creat()函数");
	fpe( " ------------------------------------------ ");
} //endl-creat_usage

void close_usage(){
	fpe( " Usage : close(int) ");
	fpe( " ------------------------------------------ ");
	fpe( " #include <unistd.h> ");
	fpe( " int close(int flages) ");
	fpe( " ------------------------------------------ ");
	fpe( " ps: 关闭一个文件时还会释放该进程加在该文件上的所有记录锁");
	fpe( " return : 成功返回0,失败返回-1 ");
	fpe( " ------------------------------------------ ");
} //endl-close_usage

void lseek_usage(){
	fpe( " Usage : lseek(int, off_t, int)" );
	fpe( " ------------------------------------------ ");
	fpe( " #include <unistd.h> ");
	fpe( " off_t lseek(int filedes, off_t offset, int whence) ");
	fpe( " ------------------------------------------ ");
	fpe( " --whence-- ");
	fpe( " whence: SEEK_SET,则将该文件的偏移量设为距文件开始处offset个字节");
	fpe( " whence: SEEK_CUR,则将该文件的偏移量设为其当前值加offset,offset可正可负");
	fpe( " whence: SEEK_END,则将该文件的偏移量设为文件长度加offset,offset可正可负");
	fpe( " return : 若成功执行，则返回新的文件偏移量");
	fpe( " ------------------------------------------ ");
}

void read_usage(){
	fpe( " Usage : read(int, void, size_t) ");
	fpe( " ------------------------------------------ ");
	fpe( " #include <unistd.h> ");
	fpe( " ssize_t read(int filedes, void *buf, size_t nbytes) ");
	fpe( " ------------------------------------------ ");
	fpe( " 调用read函数从打开的文件中读数据");
	fpe( " 如果read成功，返回字节数，如果已到达文件结尾，返回0 ");
} //endl-read_usage()

void write_usage(){
	fpe( " Usage : write(int, void, size_t)");
	fpe( " ------------------------------------------ ");
	fpe( " #include <unistd.h> ");
	fpe( " ssize_t write(int filedes, const void *buf, size_t nbytes) ");
	fpe( " ------------------------------------------ ");
	fpe( " return: 成功返回字节数，失败返回-1");
	fpe( " 对于普通文件，写操作从文件当前偏移量处开始，如果打开文件时,指定O_APPEND选项");
	fpe( " 则在每次写操作之前，将文件偏移量设置在文件的当前结尾处。在一次成功写之后，");
	fpe( " 该文件偏移量增加实际写的字节数");
} //endl-write_usage()

void fcntl_usage(){
	fpe( " Usage : fcntl(int, int, ...) ");
	fpe( " ------------------------------------------ ");
	fpe( " #include <fcntl.h> ");
	fpe( " int fcntl(int filedes, int cmd, ... [int arg]) ");
	fpe( " ------------------------------------------ ");
	fpe( " --cmd-- ");
	fpe( " cmd = F_DUPFD: 复制一个现有的描述符 ");
	fpe( " cmd = F_GETFD | F_SETFD : 获得|设置文件描述符标记");
	fpe( " cmd = F_GETFL | F_SETFL : 获得|设置文件状态标志");
	fpe( " cmd = F_GETOWN | F_SETOWN : 获得|设置异步io所有权");
	fpe( " cmd = F_GETLK | F_SETLK |F_SETLKW : 获得|设置记录锁");
	fpe( " ------------------------------------------ ");
}

void sync_usage(){
	fpe( " Usage : sync(void) & fsync(int) & fdatasync(int) ");
	fpe( " ------------------------------------------ ");
	fpe( " #include <unistd.h> ");
	fpe( " int fsync(int filedes) ");
	fpe( " int fdatasync(int filedes) ");
	fpe( " void sync(void) ");
	fpe( " ------------------------------------------ ");
	fpe( " sync  : 将所有修改过的块缓冲区排入写队列，然后返回，它并不订带实际写磁盘的操作。");
	fpe( " fsync : 只对由文件描述符filedes指定的单一文件起作用，并且等待写操作结束，然后返回。");
	fpe( " fdatasync : 类似fsync，它只影响文件的数据部分，除数据外，fsync还会同步更新文件的属性。");
	fpe( " ------------------------------------------ ");
}

void fileIO_usage(){
	fpe( " Usage : fileIO_usage -h");
	fpe( "         main -h {open,creat,close,lseek,read,write,fcntl}");
	fpe( "         main -r {open,creat,close,lseek,read,write,fcntl}");
}


























