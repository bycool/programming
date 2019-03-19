#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define FILE_NUM 20   //每个子目录要创建多少个文件
#define SUBDIR_NUM 12    //目录下需要多少个子目录
#define FILE_SIZE 100 //FILE_SIZE * 64 = file_size  不超过64字节的数据向一个文件写多少次

#define MONTHOFYEAR 12
#define STARTYEAR 2010
#define STOPYEAR 2018

#define BASE_DIR "./t1"

int sig_quit = 0;

void sig_thread(){
	printf("ctrl+c\n");
	sig_quit = 1;
}

//......................................perpare.......................................//
int getdaysofmonth(int year, int month){
	int day = 0;
	int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if(month==2){
		day = ((year%4==0)&&(year%100!=0) || (year%400==0))?29:28;
	}else{
		day = days[month-1];
	}
	return day;
}

void createdir(const char* path){
    if(access(path, F_OK) == -1){
        mkdir(path, 0755);
    }
}

void writefile2dir(const char* basedir){
	char filename[64] = { 0 };
	char buf[64] = { 0 };
	int fd = -1;
	int file_num = 1;
	int file_size = 0;

	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	sprintf(buf, "[q|%d.%d]", tv.tv_sec, tv.tv_usec);

	do{
		sprintf(filename, "%s/%d.txt", basedir, file_num);
		printf("init: %s\n", filename);
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0600);
		for(file_size=0; file_size < FILE_SIZE; file_size++){
			write(fd, buf, strlen(buf));
		}
		close(fd);
	}while(file_num++ < FILE_NUM);
}

void preparefullfile(){
	char path[128] = { "./test"};
	createdir(path);
	int years = 0;
	int months = 0;
	int days = 0;
	int daysofmonth = 0;
	for(years=STARTYEAR; years<=STOPYEAR; years++){
		sprintf(path, "%s/%d", BASE_DIR, years);
		createdir(path);
		for(months=1; months<=MONTHOFYEAR; months++){
			sprintf(path, "%s/%d/%d", BASE_DIR, years, months);
			createdir(path);
			daysofmonth = getdaysofmonth(years, months);
			for(days=1; days<daysofmonth; days++){
				sprintf(path, "%s/%d/%d/%d", BASE_DIR, years, months, days);
				createdir(path);
				writefile2dir(path);
			}
		}
	}
}
//.....................................perpare.......................................//

//.....................................writing.......................................//

char* get_random_file_path(char* filepath){
	char buf[128] = { 0 };
	struct timeval tv;
    struct timezone tz;

	int years = 0;
	int months = 0;
	int days = 0;
	int files = 0;
	while(access(buf, F_OK) == -1){
		gettimeofday(&tv,&tz);
	    years = STARTYEAR + (tv.tv_sec + tv.tv_usec) % (STOPYEAR-STARTYEAR);
	    months = tv.tv_usec%12;
	    days = (tv.tv_sec + tv.tv_usec) % getdaysofmonth(years,months);
	    files = (tv.tv_usec + tv.tv_sec) % FILE_NUM;

		sprintf(buf,"%s/%d/%d/%d/%d.txt", BASE_DIR, years, months, days, files);
	}
	memcpy(filepath, buf, strlen(buf));
	
}

char* get_random_dir_path(char* filepath){
    char buf[128] = { 0 };
    struct timeval tv;
    struct timezone tz;

    int years = 0;
    int months = 0;
    int days = 0;
    int files = 0;
    while(access(buf, F_OK) == -1){
        gettimeofday(&tv,&tz);
        years = STARTYEAR + (tv.tv_sec + tv.tv_usec) % (STOPYEAR-STARTYEAR);
        months = tv.tv_usec%12;
        days = (tv.tv_sec + tv.tv_usec) % getdaysofmonth(years,months);

        sprintf(buf,"%s/%d/%d/%d", BASE_DIR, years, months, days);
    }
    memcpy(filepath, buf, strlen(buf));

}


void random_op_write(){
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);

    char buf[32] = { 0 };
    sprintf(buf, "[w|%d.%d]", tv.tv_sec, tv.tv_usec);

	int fd = -1;
	char path[128] = { 0 };
	get_random_file_path(path);
	printf("random_write: %s\n", path);
	fd = open(path, O_WRONLY | O_APPEND, 0600);
	write(fd, buf, strlen(buf));
	close(fd);
}
void random_op_rename(){
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);

	char path[128] = { 0 };
	char tmpath[128] = { 0 };
	int years = STARTYEAR + (tv.tv_sec + tv.tv_usec)%(STOPYEAR-STARTYEAR);
	int months = (tv.tv_sec + tv.tv_usec) % 12;
	int days = (tv.tv_sec + tv.tv_usec) % getdaysofmonth(years,months);
	int files = (tv.tv_sec + tv.tv_usec) % FILE_NUM;
	sprintf(path,"%s/%d/%d/%d/%d.txt", BASE_DIR, years, months, days, files);
	if(access(path, F_OK) == -1)return;
	sprintf(tmpath, "%s.rename", path);
	if(access(tmpath, F_OK) == 0) return;
	rename(path, tmpath);
	printf("rename: %s to %s\n");
}

void random_op_open_create_write_close(){
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv,&tz);

    char buf[32] = { 0 };
    sprintf(buf, "[ocwc|%d.%d]", tv.tv_sec, tv.tv_usec);

	int fd = -1;
	char path[128] = { 0 };
	int years = STARTYEAR + (tv.tv_sec + tv.tv_usec)%(STOPYEAR-STARTYEAR);
	int months = (tv.tv_sec + tv.tv_usec) % 12;
    int days = (tv.tv_sec + tv.tv_usec) % getdaysofmonth(years,months);
    int files = (tv.tv_sec + tv.tv_usec) % FILE_NUM;
	sprintf(path,"%s/%d/%d/%d/%d.txt", BASE_DIR, years ,months, days, files);
	if(access(path, F_OK) == 0){
		sprintf(path,"%s.ocwc",path);
	}
	fd = open(path, O_CREAT | O_WRONLY, 0755);
	write(fd, buf, strlen(buf));
	close(fd);
}

void random_op_truncate(){
	char path[128] = { 0 };
	get_random_file_path(path);
	truncate(path, 10);
	printf("truncate: %s\n", path);

    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);

    char buf[32] = { 0 };
    sprintf(buf, "[tc|%d.%d]", tv.tv_sec, tv.tv_usec);

	int fd = open(path, O_WRONLY | O_APPEND, 0600);
	write(fd, buf, strlen(buf));
	close(fd);
}

void random_op_open_lseek_write_close(){
    char path[128] = { 0 };
    get_random_file_path(path);

    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);

	char buf[32] = { 0 };
	sprintf(buf, "[olwc|%d.%d]", tv.tv_sec, tv.tv_usec);

	int fd = open(path, O_WRONLY, 0600);
	lseek(fd, 10, SEEK_SET);
	write(fd, buf, strlen(buf));
	close(fd);
}

void random_op_mkdir_rmdir(){
	char path[128] = { 0 };
	get_random_dir_path(path);

	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	sprintf(path, "%s/%d_mkdir", path, tv.tv_sec);
	if(access(path, F_OK)==-1){
		mkdir(path, 0777);
	//	rmdir(path);
	}
}

void random_op_unlink(){
	char path[128] = { 0 };
	get_random_file_path(path);

	unlink(path);

	printf("unlink: %s\n", path);

	sprintf(path, "%s.unlink", path);
	int fd = open(path, O_CREAT | O_WRONLY, 0600);
	write(fd, "unlink", 6);
	close(fd);
}

void random_op_link(){
	char path[128] = { 0 };
	char linkpath[128] = { 0 };
	get_random_file_path(path);

	sprintf(linkpath, "%s.link", path);
	if(access(linkpath, F_OK) == -1)
		link(path, linkpath);
}

void random_op_symlink(){
	char path[128] = { 0 };
	char sympath[128] = { 0 };
	get_random_file_path(path);

	sprintf(sympath, "%s.symlink", path);
	if(access(sympath, F_OK) == -1)
		symlink(path, sympath);
}


//.....................................writing.......................................//

//create thread
void* rand_write(){
	while(!sig_quit){
		random_op_write();
		usleep(400000);
	}
}

void* rand_rename(){
	while(!sig_quit){
		random_op_rename();
		usleep(500000);
	}
}

void* rand_open_create_write_close(){
	while(!sig_quit){
		random_op_open_create_write_close();
		usleep(700);
	}
}

void* rand_truncate(){
	while(!sig_quit){
		random_op_truncate();
		sleep(1);
	}
}

void* rand_open_lseek_write_close(){
	while(!sig_quit){
		random_op_open_lseek_write_close();
		sleep(1);
	}
}

void* rand_mkdir_rmdir(){
	while(!sig_quit){
		random_op_mkdir_rmdir();
		sleep(1);
	}
}

void* rand_unlink(){
	while(!sig_quit){
		random_op_unlink();
		sleep(1);
	}
}

void* rand_link(){
	while(!sig_quit){
		random_op_link();
		sleep(1);
	}
}

void* rand_symlink(){
	while(!sig_quit){
		random_op_symlink();
		sleep(1);
	}
}

void thread_inc(){
	pthread_t t1, t2, t3, t4, t5, t6, t7,t8, t9;
#if 1
	pthread_create(&t1, NULL, rand_write, NULL);
	pthread_create(&t2, NULL, rand_rename, NULL);
#endif 
	pthread_create(&t3, NULL, rand_open_create_write_close, NULL);
#if 1
	pthread_create(&t4, NULL, rand_truncate, NULL);
	pthread_create(&t5, NULL, rand_open_lseek_write_close, NULL);
	pthread_create(&t6, NULL, rand_mkdir_rmdir, NULL);
	pthread_create(&t7, NULL, rand_unlink, NULL);
	pthread_create(&t8, NULL, rand_link, NULL);
	pthread_create(&t9, NULL, rand_symlink NULL);
	pthread_detach(t1);
	pthread_detach(t2);
	pthread_detach(t4);
	pthread_detach(t5);
	pthread_detach(t6);
	pthread_detach(t7);
	pthread_detach(t8);
	pthread_detach(t9);
#endif
	pthread_detach(t3);
	pthread_exit(NULL);
}


int main(int argc, char* argv[]){
	int opt;
	char filepath[128] = { 0 };

	signal(SIGINT, sig_thread);

	if(argc < 2){
		printf("Usage: ./fdstest {-p[prepare] | -w[write] | -c[checkresult]}\n");
		return -1;
	}

	while((opt = getopt(argc, argv, "pwct"))!=-1){
		switch(opt)
		{
			case 'p':
				preparefullfile();
				break;
			case 'w':
//				random_op_write();
				thread_inc();
				break;
			case 'c':

				break;
			case 't':
				get_random_file_path(filepath);
				break;
			default:
				printf("Usage: ./fdstest {-p[prepare] | -w[write] | -c[checkresult]}\n");
				break;
		}
	}
	return 0;
}
