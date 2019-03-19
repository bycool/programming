#define _LARGEFILE64_SOURCE

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

#include "config.h"

#ifndef SOFT_PLATFORM_CYGWIN
#include <sys/wait.h>
#include <unistd.h>
#define MAX_PATH PATH_MAX
#else
#include <direct.h>
#endif

#include "ora_opt.h"
#include "fzs_data_type.h"
#include "recv_queue.h"
#include "fzs_tcp.h"
#include "zlog.h"
#include "put_conf.h"
#include "monitor.h"
#include "bytes_value_conv.h"
#include "fzs_mem.h"
#include "os_file.h"
#include "process.h"
#include "sendlog.h"
#include "fzs_md5.h"
#include "scn_time.h"
#include "xml_item.h"
#include "atoll.h"
#include "fdsload.h"


#define TASK_INFO_LEN	6*1024*1024

zlog_category_t *fzs_log = 0;

static char strcur_path[MAXPATH] = "";

PARAM_T *pparam_t;
TGT_T* tgt_t;

static int shm_m = -1;
struct PID_FZS *shm = 0;
int ishm_index = -1;
int gis_exit = 0;

int gqueue_id = 0;

char srcpath[4096] = {0};
char tarpath[4096] = {0};


void sig_quit(int sig)
{
    printf("cdpback %d quit exception sig %d \n", sig);
    usleep(1000);
    exit(0);
}


void print_usage(){
	printf("Example : cdp -c load.conf\n");
	printf("Example : cdp -c load.conf -b 12\n");
}




int XML_get_task_item(char* pbufxml, char* pitem, char* pattr, char* pval){
	
	char* ptmp = NULL;
	char* pend = NULL;

	if(pval){
		*pval = 0;
	}
	if(!pbufxml || !pbufxml[0]){
		return -1;
	}

	ptmp = pbufxml;
	while((ptmp=strchr(ptmp, ' '))!=NULL){
		ptmp++;
		if(strncmp(ptmp, pattr, strlen(pattr))==0){
			ptmp += strlen(pattr)+2;
			pend = strchr(ptmp,'"');
			strncpy(pval, ptmp, pend-ptmp);
			break;
		}
	}
}

static UB8 cdp_time2num(char *pstr_time)
{
    struct tm tm_str;

    tm_str.tm_wday = 0;
    tm_str.tm_yday = 0;
    tm_str.tm_isdst = 0;

    sscanf(pstr_time, 
            "%d-%d-%d,%d:%d:%d", 
            &(tm_str.tm_year), 
            &(tm_str.tm_mon),
            &(tm_str.tm_mday),
            &(tm_str.tm_hour),
            &(tm_str.tm_min),
            &(tm_str.tm_sec));

    tm_str.tm_year -= 1900;
    tm_str.tm_mon--;

    return mktime(&tm_str);
}



void get_task_info(int tgt_id, int task_id, char* item, char* mode, char* filename, char* backtime, char* outdir, char* srcip, char* srcport){
	FILE* fp = NULL;
	char xml_path[64] = {0};
	char buf[32] = {0};
	char* task_info = NULL;

	sprintf(xml_path, "./fzs_tgt/%d/cdpTasks.xml", tgt_id);
	fp = fopen(xml_path, "r");
	if(!fp){
		printf("fopen file %s failed, errMsg: %s\n", xml_path, strerror(errno));
		zlog_error("fopen file %s failed, errMsg: %s", xml_path, strerror(errno));
		return -1;;
	}

	task_info = (char*)malloc(TASK_INFO_LEN);

	while(!feof(fp)){
		fgets(task_info, TASK_INFO_LEN, fp);
//		XML_get_item(task_info, item, "taskid", buf);
		XML_get_task_item(task_info, item, "taskid", buf);
		if(atoi(buf) != task_id)
			continue;
		XML_get_task_item(task_info, item, "mode", mode);
		XML_get_task_item(task_info, item, "backtime", backtime);
		XML_get_task_item(task_info, item, "filename", filename);
		XML_get_task_item(task_info, item, "ip", srcip);
		XML_get_task_item(task_info, item, "port", srcport);
		XML_get_task_item(task_info, item, "outdir", outdir);
#if 0
		XML_get_item(task_info, item, "mode", mode);
		XML_get_item(task_info, item, "backtime", backtime);
		XML_get_item(task_info, item, "filename", filename);
		XML_get_item(task_info, item, "ip", srcip);
		XML_get_item(task_info, item, "port", srcport);
		XML_get_item(task_info, item, "outdir", outdir);
#endif
		break;
	}
	fclose(fp);
	free(task_info);
}

// /home/ten/source/1/3/2/t/
#if 1

void copy_file(char* srcfile, char *tardir){
	int rc = -1;
	FILE* srcfp = NULL;
	FILE* tarfp = NULL;
	struct stat tst;
	char tarfile[4096] = {0};
	char* filename = NULL;
	char readbuf[4096] = {0};

	if(stat(srcfile, &tst)<0){
		printf("Get %s stat fail\n", srcfile);
		return ;
	}

	rc = strlen(srcfile);
	while(srcfile[rc]!='/')
		rc--;
	filename = &srcfile[rc];

	sprintf(tarfile, "%s%s", tardir, filename);

	srcfp = fopen(srcfile, "r");
	tarfp = fopen(tarfile, "w+");
	while(!feof(srcfp)){
		rc = fread(readbuf, 1, sizeof(readbuf), srcfp);
		fwrite(readbuf, rc, 1, tarfp);
	}
	fclose(srcfp);
	fclose(tarfp);
}


void copy_dir_r(char* srcdir, char* tardir){
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

		sprintf(tarpath, "%s%s", tardir, pdirent->d_name);
		sprintf(srcpath, "%s%s", srcdir, pdirent->d_name);

		stat(srcpath, &tst);
		if(!S_ISDIR(tst.st_mode)){
			srcfp = fopen(srcpath,"r");
			tarfp = fopen(tarpath, "w+");
			if(!srcfp && !tarfp) printf(" srcfp tarfp NULL\n");

			while(!feof(srcfp)){
				rc = fread(readbuf, 1, sizeof(readbuf), srcfp);
				fwrite(readbuf, sizeof(readbuf), 1, tarfp);
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
			copy_dir_r(srcpath, tarpath);
		}
	}
}

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

//   filename: /home/test/1.txt  /home/test/
//   outdir  : /home/ten/tmp/  must be dir with '/'
void mkdir_copy_src_to_tar(char* filename, char* outdir){
	
    int rc = -1;
	int if_file = -1;
    struct stat fst;
    char* tmpfilename = NULL;
    char* p = NULL;
    char path[4096] = {0};

    if(!outdir || outdir[0]!='/'){
        printf("!outdir\n");
        return ;
    }
    if(!filename || filename[0]!='/'){
        printf("!filename\n");
        return ;
    }

	rc = strlen(filename);
	
	if(filename[rc-1] != '/'){
		if_file = 1;
	}

	if(stat(outdir, &fst)<0){
		printf("Get %s stat fail\n", outdir);
		return ;
	}
	if(!S_ISDIR(fst.st_mode)){
		printf("Path %s is NOT DIR\n", outdir);
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


	if(if_file==1){
    	rc = strlen(path);
    	while(path[rc] != '/'){
           	path[rc] = '\0';
           	rc--;
    	}
	}

	mkdirp(path);

	if(if_file==1){
		copy_file(filename, path);
	}else{
		copy_dir_r(filename, path);
	}
}
#endif

int cdp_load_create_outdir(int tgt_id, FZS_FCREATE* pfzs, char* outdir){
	char filename[MAXPATH];
	char *p = NULL;
	int fd = -1;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc -1;
	sprintf(p, "%s", pfzs->filename);

	if(pfzs->is_full)
		return 0;

	if(file_exist(filename)){
		printf("file: %s exist when create\n", filename);
	}
	umask(0);

	fd = open(filename, O_WRONLY|O_CREAT|(O_TRUNC&pfzs->flag), pfzs->mode);

	if(fd<0){
		printf("create file:%s error:%s\n",filename, strerror(errno));
		goto ret;
	}

	close(fd);
	rc = 0;
ret:
	if(rc >= 0){
		uid_t uid = pfzs->uid;
		gid_t gid = pfzs->gid;

		if(lchown(filename, uid, gid)!=0){
			printf("chown file:%s error:%s\n", filename, strerror(errno));
		}
	}
	return rc;
}

mode_t cdp_getmode(char* pathname){
	struct stat fst;

	if(!lstat(pathname, &fst))
		return fst.st_mode;

	return -1;
}

int cdp_rmfile(char *pathname)
{
    mode_t mode=cdp_getmode(pathname);
    if(mode==-1)
        return -1;

    if(S_ISDIR(mode)){
        DIR *dir;
        if((dir=opendir(pathname))){
            struct dirent *dirrent;
            while( (dirrent=readdir(dir))){
                char npathname[MAXPATH];
                if(!strcmp(dirrent->d_name,".")||!strcmp(dirrent->d_name,"..")){
                    continue;
                }
                getpathname(pathname,dirrent->d_name,npathname);
                if(cdp_rmfile(npathname)){
                    return -1;
                }
            }
            closedir(dir);
        }else{
            return -1;
		}
        return rmdir(pathname);
    }
    return UNLINK(pathname);
}

int cdp_load_del_outdir(int tgt_id, FZS_FDELETE* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc -1;
	sprintf(p, "%s", pfzs->filename);

	if(!file_exist(filename)){
		printf("unlink file:%s not exist\n", filename);
		rc = 0;
		goto ret;
	}

	rc = cdp_rmfile(filename);
	if(rc<0){
		printf("remove file:%s error:%s\n", filename, strerror(errno));
		goto ret;
	}

ret:
	return rc;
}

int cdp_load_write_outdir(int tgt_id, FZS_FWRITE* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int fd = -1;
	int rc = -1;
	int if_disp_err = 0;
	int if_been_error = 0;
	int if_write_ok = 0;
	unsigned long off = 0;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	if(pfzs->no_data)
		return 0;

	fd = open(filename, O_WRONLY|O_CREAT, fzs_os_file_mode(0));
	if(fd<0){
		printf("write.open file %s error: %s\n", filename, strerror(errno));
		goto ret;
	}

	off = lseek64(fd, pfzs->file_offset, SEEK_SET);
	if(off<0){
		printf("lseek file: %s offset:%lu, error:%s\n", filename,pfzs->file_offset, strerror(errno));
		goto ret;
	}
	
	if_disp_err = 1;
	while(pfzs->write_length != write(fd, pfzs->content, pfzs->write_length)){
		if(if_disp_err){
			printf("write file: %s, offset:%lu, error:%s\n", filename, pfzs->file_offset, strerror(errno));
			if_disp_err = 0;
		}

		if(errno == ENOSPC || errno == EINTR || errno == ENOMEM){
			lseek64(fd, off, SEEK_SET);
			if_been_error = 1;
			sleep(1);
			continue;
		}

		if_been_error = 1;
		if_write_ok = 0;
		break;
	}
	close(fd);

	if(if_write_ok){
		rc = 0;
	}

ret:
	return rc;
}

int cdp_load_truncate_outdir(int tgt_id, FZS_FTRUNCATE* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int fd = -1;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	fd = open(filename, O_WRONLY|O_CREAT, fzs_os_file_mode(0));
	if(fd<0){
		printf("open file:%s error:%s\n", filename, strerror(errno));
		goto ret;
	}

	if(sizeof(off_t)&&pfzs->file_offset > 0xFFFFFFFF){
		printf("truncate file:%s size:%lu, too large", filename, pfzs->file_offset);
	}else{
		rc = ftruncate(fd, pfzs->file_offset);
		if(rc<0){
			printf("truncate file: %s error:%s\n", filename, strerror(errno));
			goto ret;
		}
	}
	rc = 0;
ret:
	return rc;
}

int cdp_load_rename_outdir(int tgt_id, FZS_FRENAME *pfzs, char* outdir){
	char filename[MAXPATH];
	char newfile[MAXPATH];
	char* p = NULL;
	int rc = -1;
	int flen = 0;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);
	rc = snprintf(newfile, MAXPATH, "%s", outdir);
	p = newfile + rc - 1;
	sprintf(p, "%s", pfzs->newfilename);

	if(!file_exist(filename)){
		rc = 0;
		goto ret;
	}

	if(file_exist(newfile)){
		cdp_rmfile(newfile);
	}

	rc = rename(filename, newfile);
	if(rc<0){
		printf("rename file: %s to newfile: %s error: %s\n", filename, newfile, strerror(errno));
		goto ret;
	}

	flen = strlen(filename);
	if(flen >= 5 && !strcmp(&(filename[flen-5]), "_@fts")){
		printf("rename.unlink file: %s\n", filename);
		unlink(filename);
	}

ret:
	return rc;
}

int cdp_load_dircreate_outdir(int tgt_id, FZS_DIRCREATE *pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	if(pfzs->is_full){
		return 0;
	}

	if(file_exist(filename)){
		printf("create dir : %s is exist\n", filename);
		rc = 0;
		goto ret;
	}

	umask(0);
	rc = mkdir(filename, pfzs->mode);
	if(rc<0){
		printf("crate dir: %s error:%s\n", filename, strerror(errno));
		goto ret;
	}
ret:
	if(rc>=0){
		uid_t uid = pfzs->uid;
		gid_t gid = pfzs->gid;

		if(lchown(filename, uid, gid) != 0){
			printf("chown file: %s error: %s\n", filename, strerror(errno));
		}
	}
	return rc;
}

int cdp_load_dirdel_outdir(int tgt_id, FZS_DIRDELETE* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	if(!file_exist(filename)){
		printf("remove dir: %s not exist\n", filename);
		rc = 0;
		goto ret;
	}

	rc = cdp_rmfile(filename);
	if(rc<0){
		printf("remove dir: %s error:%s\n", filename, strerror(errno));
		goto ret;
	}
ret:
	return rc;
}

int cdp_load_dirrename_outdir(int tgt_id, FZS_DIRRENAME* pfzs, char* outdir){
	char filename[MAXPATH];
	char newfile[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	rc = snprintf(newfile, MAXPATH, "%s", outdir);
	p = newfile + rc - 1;
	sprintf(p, "%s", pfzs->newfilename);

	rc = rename(filename, newfile);
	if(rc<0){
		printf("rename folder:%s to new folder:%s error:%s\n", filename, newfile, strerror(errno));
		goto ret;
	}
ret:
	return rc;
}

int cdp_load_chmod_outdir(int tgt_id, FZS_FCHMOD* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	if(!file_exist(filename)){
		printf("chmod file: %s is not exist\n", filename);
		rc = 0;
		goto ret;
	}

	rc = chmod(filename, pfzs->mode&0777);
	if(rc<0){
		printf("chmod: %s error:%s\n", filename, strerror(errno));
		goto ret;
	}

ret:
	return rc;
}


int cdp_load_chown_outdir(int tgt_id, FZS_FCHOWN* pfzs, char* outdir){
	char filename[MAXPATH];
	char* p = NULL;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->filename);

	if(!file_exist(filename)){
		printf("chown file %s is not exist\n", filename);
		rc = 0;
		goto ret;
	}

	rc = chown(filename, (int)pfzs->uid, (int)pfzs->gid);
	if(rc<0){
		printf("chown file: %s error:%s\n", filename, strerror(errno));
		goto ret;
	}

ret:
	return rc;
}

int cdp_load_link(int tgt_id, FZS_SYMLINK* pfzs, char* outdir){
	char filename[MAXPATH];
	char linkname[MAXPATH];
	char* p = NULL;
	uid_t uid;
	gid_t gid;
	int rc = -1;

	rc = snprintf(filename, MAXPATH, "%s", outdir);
	p = filename + rc - 1;
	sprintf(p, "%s", pfzs->symlink_info);
	rc = snprintf(linkname, MAXPATH, "%s", outdir);
	p = linkname + rc - 1;
	sprintf(p, "%s", pfzs->symlinkname);

	if(pfzs->op_code = OP_LINK){
		rc = link(filename, linkname);
	}else{
		rc = symlink(filename, linkname);
	}

	if(rc != 0){
		printf("fail to create link file:%s to %s, error:%s\n", filename, linkname, strerror(errno));
		return -1;
	}

	uid = pfzs->uid;
	gid = pfzs->gid;

	if(lchown(linkname, uid, gid) != 0){
		printf("fail to change owner of file: %s\n", linkname);
	}
	return 0;

}

void cdp_load_fzs_outdir(int tgt_id, FZS* pfzs, char* outdir){
	if(!outdir){
		return ;
	}
	switch(pfzs->nil.op_code)
	{
		case OP_FCREATE:
			cdp_load_create_outdir(tgt_id, &pfzs->fcreate, outdir);
			break;
		case OP_FDEL:
			cdp_load_del_outdir(tgt_id, &pfzs->fdelete, outdir);
			break;
		case OP_FWRITE:
			cdp_load_write_outdir(tgt_id, &pfzs->fwrite, outdir);
			break;
		case OP_FTRUNCATE:
			cdp_load_truncate_outdir(tgt_id, &pfzs->filetruncate, outdir);
			break;
		case OP_FRENAME:
			cdp_load_rename_outdir(tgt_id, &pfzs->frename, outdir);
			break;
		case OP_DIRCREATE:
			cdp_load_dircreate_outdir(tgt_id, &pfzs->dircreate, outdir);
			break;
		case OP_DIRDEL:
			cdp_load_dirdel_outdir(tgt_id, &pfzs->dirdelete, outdir);
			break;
		case OP_DIRRENAME:
			cdp_load_dirrename_outdir(tgt_id, &pfzs->dirrename, outdir);
			break;
		case OP_FCHMOD:
			cdp_load_chmod_outdir(tgt_id, &pfzs->fchmod, outdir);
			break;
		case OP_FCHOWN:
			cdp_load_chown_outdir(tgt_id, &pfzs->fchown, outdir);
			break;
		case OP_FCLOSE:
			//cdp_load_close_outdir(tgt_id, &pfzs->fclose, outdir);
			break;
		case OP_FMD5:
			//cdp_load_md5_outdir(tgt_id, &pfzs->fmd5, outdir);
			break;
		case OP_LINK:
		case OP_SYMLINK:
			cdp_load_link(tgt_id, &pfzs->sym_link, outdir);
			break;
		default:
			break;
	}
}



int main(int argc, char* argv[]){
	//sleep(60);
	int rc = -1;
	int queue_id = 0;
	int tgt_id = 1;
	int ch ;
	int if_src_use = 0;

	int sock_s = -1;
	int sock_c = -1;

	int task_id = -1;
	char mode[8] = {0};
	char outdir[MAXPATH] = {0};
	char backtime[32] = {0};
	char filename[MAXPATH] = {0};
	char srcip[32] = {0};
	char srcport[16] = {0};

	pthread_t stop_thread;

	if(argc<3){
		print_usage();
		return -1;
	}

#if 0
	if(fork()){
		_exit(0);
	}
#endif

	signal(SIGTERM, sig_quit);
	signal(SIGABRT, sig_quit);
	signal(SIGSEGV, sig_quit);
	signal(SIGFPE, sig_quit);

	rc = zlog_init("../conf/fzs_log.conf");
	if(rc)
	{
		printf("init fail\n");
		return -1;
	}

	fzs_log = zlog_get_category("fzs");
	if(!fzs_log){
		printf("get fzs fail\n");
		zlog_fini();
		return -2;
	}

	init_zlog_lib_mod(fzs_log);

	getcwd(strcur_path, sizeof(strcur_path));

	while((ch = getopt(argc, argv, "c:d:s")) != -1){
		switch(ch)
		{
			case 'c':
				put_conf_info(optarg);
				get_param_t(&pparam_t);
				get_tgt_t(&tgt_t);
				break;
			case 'd':
				task_id = atoi(optarg);
				break;
			case 's':
				if_src_use = 1;
				break;
			default:
				break;
		}

		
	}

#if 0
	if(if_src_use){

	}
#endif
	printf("+-------------------fzs cdp %d started-----------------------+\n", queue_id);
	
	get_task_info(tgt_id, task_id, "cdpTask", mode, filename, backtime, outdir, srcip, srcport);
//	printf("mode:%s, filename:%s, backtime:%s, outdir:%s, srcip:%s srcport:%s\n",mode, filename, backtime, outdir, srcip, srcport);

	if(strcmp(mode,"host")){
		printf("need connect to src, handle it soon\n");
	//	return -1;
	}

	//cp target to outdir
#if 0
	shm_m = shm_fzs_open(FZS_WHO_TGT ,0, 0);
	if(shm_m == -1)
		goto ret;

	shm = (struct FZS_PID*)shmat(shm_m, 0, 0);
	if(!shm)
		printf("cdpback-- shm is null\n");

/*	rc = pthread_create(&stop_thread, NULL, pfstop, NULL);
	if(rc){
		printf("pfstop thread create fail, main process exit\n");
		exit(EXIT_FAILURE);
	}
*/
#endif
	//cp filename to outdir, outdir must be dir and exist ex:/tmp/
	//1.filename is file, maybe is not exist, ex:/home/ten/source/1.txt, then mkdir /tmp/home/ten/source/
	//2.filename is dir, ex:/home/ten/source/, maybe is not exist, then mkdir /tmp/home/ten/source/
	mkdir_copy_src_to_tar(filename, outdir);

	if(pparam_t->param_if_save_rbk){
		int fzs_h = 0;
		int fzs_l = 0;
		int t_fzs = 0;
		char tmp_file[MAX_PATH];
		FILE* fp = NULL;
		int fd = -1;


		sprintf(tmp_file, "./queue/%d", queue_id);
		FILE* fqueue = fopen(tmp_file, "rb");
		if(!fqueue){
			printf("there is not any fzs file\n");
			goto ret;
		}

		fread(tmp_file, sizeof(tmp_file), 1, fqueue);
		sscanf(tmp_file, "%d %d %ld", &fzs_l, &fzs_h, &t_fzs);

		printf("fzsl: %d, fzs_h: %d\n", fzs_l, fzs_h);

		// begin back find fzs.info from .bzs file
		for(t_fzs = fzs_h; t_fzs >= fzs_l; t_fzs--){
			char* fzs_buf = NULL;
			char lenfzs[4];
			unsigned int fzslen = 0;
			char* pfzs = 0;
			

			sprintf(tmp_file, "./fzs_tgt/%d/%d/%d.%d.bzs", tgt_id, t_fzs/FILE_NUM_EACH_DIR, t_fzs, queue_id);
			fd = open(tmp_file, O_RDONLY, 0600);
			printf("open bzs: %s --------------\n", tmp_file);
			if(fd<0){
				printf("open %s fail\n", tmp_file);
				break;
			}
			lseek(fd, 0, SEEK_END);

			while(1){
				if(lseek(fd, -4, SEEK_CUR)<0){
					printf("read %s finish\n", tmp_file);
					break;
				}
				if(read(fd, lenfzs, 4) != 4){
					printf("read %s fzs buf len error\n", tmp_file);
					close(fd);
					goto ret;
				}
				fzslen = GET4(lenfzs);

				if(fzs_buf){
					free(fzs_buf);
					fzs_buf = NULL;
				}

				fzs_buf = (char*)malloc(fzslen+4);
				if(!fzs_buf){
					printf("file:%s, line:%d: malloc size:%u fail\n", __FILE__, __LINE__, fzslen+4);
					close(fd);
					goto ret;
				}
				
				memcpy(fzs_buf, lenfzs, 4);
				lseek(fd, -((int)fzslen), SEEK_CUR);
				if(read(fd, fzs_buf+4, fzslen) != fzslen){
					printf("read %s fzs buf error, size: %u\n", tmp_file, fzslen);
					free(fzs_buf);
					fzs_buf = NULL;
					close(fd);
					goto ret;
				}
				lseek(fd, -((int)fzslen+4), SEEK_CUR);

				unsigned char op_code = GET1(fzs_buf+4);
				char back_name[MAXPATH] = {0};

				unsigned int back_name_len = GET4(fzs_buf + 4 + 1 + 8 + 8);
				memcpy(back_name, fzs_buf + 17 + 8, back_name_len);

				unsigned long mtime = GET8(fzs_buf + 4 + 1);
				unsigned long timenum = cdp_time2num(backtime);

				//get the org path, and time earlier
				if(!strstr(filename, back_name) && mtime <= timenum){
					printf("gotcha\n");

					pfzs = (FZS*)malloc(sizeof(FZS));
					buf2fzs(pfzs, fzs_buf);

					//load bzs to outdir/filename
					cdp_load_fzs_outdir(tgt_id, pfzs, outdir);
				}

			}
			
		}
	}
	
	
		
ret:
	printf("+------------------- cdpback %d exit --------------+\n", queue_id);

	zlog_fini();

	shmdt(shm);
	
	
}














