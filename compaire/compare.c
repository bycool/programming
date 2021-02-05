#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_all_empty(char*** tabname, int* bidx, int bufcnt){
	int i = 0;
	for(i=0; i<bufcnt; i++){
//		printf("bidx[%d]: %d\n", i, bidx[i]);
//		printf("tabname[%d][%d]: %s\n", i, bidx[i], tabname[i][bidx[i]]);
		if(tabname[i][bidx[i]]) {
//			printf("is_all_empty: %s\n", tabname[i][bidx[i]]);
			return 1;
		}
	}
	return 0;
}

int is_cnt_end(int* tabcnt, int* bidx, int bufcnt) {
	int i = 0;
#if 0
	printf("bidx:");
	for(i=0; i<bufcnt; i++) {
		printf("%d,", bidx[i]);
	}
	printf("\b\n");
#endif
	for(i=0; i<bufcnt; i++) {
		if(bidx[i] < tabcnt[i])
			return 1;
	}
	return 0;
}

int find_min_tab(char*** tabname, int* bidx, int bufcnt, int* fret) {
	int i = 0, min = 0;
	char* mintab = NULL;
	char* cmptab = NULL;
	for(i=0; i<bufcnt; i++) {
		cmptab = tabname[i][bidx[i]];
//		printf("%s  ", cmptab);
		if(cmptab==NULL) continue;
		if(mintab == NULL){
			mintab = cmptab;
			min = i;
			continue;
		}
		if(strcmp(cmptab, mintab)<=0){
			mintab = cmptab;
			min = i;
		}
	}
//	printf("\n");
	for(i=0; i<bufcnt; i++) {
		if(strcmp(tabname[i][bidx[i]], mintab)==0) {
			fret[i] = 1;
		}else{
			fret[i] = 0;
		}
	}
	return min;
}


int main(int argc, char* argv[]) {
	int ret = 0;
	int i = 0, j = 0;
	int idx = 0;
	int bufcnt = 0;
	int fd;
	char* p = NULL;
	char* pp = NULL;
	char* ppp = NULL;
	char* pppp = NULL;
	char** buf = NULL;
	char*** usrn = NULL;
	char*** tabn = NULL;
	char*** rows = NULL;
	int* bidx = NULL;
	int* tabcnt = NULL;
	int* fret = NULL;
	struct stat fst;


	bufcnt = argc-1;
//	printf("bufcnt: %d\n", bufcnt);
	buf = (char**)malloc(sizeof(char*)*bufcnt);
	usrn = (char***)malloc(sizeof(char**)*bufcnt);
	tabn = (char***)malloc(sizeof(char**)*bufcnt);
	rows = (char***)malloc(sizeof(char**)*bufcnt);
	
	bidx = (int*)malloc(sizeof(int)*bufcnt);
	tabcnt = (int*)malloc(sizeof(int)*bufcnt);
	fret = (int*)malloc(sizeof(int)*bufcnt);
	for(i=0; i<bufcnt; i++) {
		bidx[i] = 0;
		tabcnt[i] = 0;
		usrn[i] = (char**)malloc(sizeof(char*)*1024);
		tabn[i] = (char**)malloc(sizeof(char*)*1024);
		rows[i] = (char**)malloc(sizeof(char*)*1024);
	}
	

	for(i=0; i<bufcnt; i++) {
		fd = open(argv[i+1], O_RDONLY, 0600);
		if(fd < 0) {
			printf("open %s fail\n", argv[i+1]);
			return 0;
		}
		if(fstat(fd, &fst)==-1) {
			printf("fstat %s fail\n", argv[i+1]);
			close(fd);
			return 0;
		}
		buf[idx] = (char*)malloc(fst.st_size+1);
		ret = read(fd, buf[idx], fst.st_size);
		buf[idx][ret] = 0;
		if(ret != fst.st_size) {
			printf("read %s error [%d|%d]\n", argv[i+1], fst.st_size, ret);
			close(fd);
			return 0;
		}
		close(fd);


		for(p=buf[idx]; (p&&*p); ) {
			pp = strchr(p, '\n');
			if(!pp) pp=p+strlen(p); else { *pp=0; pp++; }
			ppp = strchr(p, '.');
			if(ppp){
				usrn[i][tabcnt[i]] = p;
				*ppp++=0;
				tabn[i][tabcnt[i]] = ppp;
				pppp = strchr(ppp, '.');
				if(pppp) {
					*pppp++ = 0;
					rows[i][tabcnt[i]] = pppp;
				}else{
					rows[i][tabcnt[i]] = 0;
				}
			}
//			printf("tabcnt[%d]: %d  :: %s ::  username: %s -- tablename: %s -- rows: %s\n", i, tabcnt[i], p, usrn[i][tabcnt[i]], tabn[i][tabcnt[i]], rows[i][tabcnt[i]]);
			tabcnt[i]++;
			p = pp;
		}
		idx++;
	}

//	printf("ret: %d\n", is_all_empty(tabn, bidx, bufcnt));
#if 1
//	while(is_all_empty(tabn, bidx, bufcnt)){
	while(is_cnt_end(tabcnt, bidx, bufcnt)) {
		ret = find_min_tab(tabn, bidx, bufcnt, fret);
		for(i=0; i<bufcnt; i++) {
			if(fret[i] == 0)
				printf("%30s","");
			else{
				printf("%30s", tabn[i][bidx[i]]);
				tabn[i][bidx[i]] = 0;
				bidx[i]++;
			}
		}
		printf("\n");
	}
#endif


#if 0
	for(i=0; i<bufcnt; i++) {
		for(j=0; j<tabcnt[i]; j++){
			printf("[%d|%d]:: %s  :: %s  :: %s\n", i,j, usrn[i][j], tabn[i][j], rows[i][j]);
		}
	}
#endif


	for(i=0; i<bufcnt; i++) {
		free(usrn[i]);
		free(tabn[i]);
		free(rows[i]);
		free(buf[i]);
	}
	free(fret);
	free(bidx);
	free(tabcnt);
	free(buf);
	free(usrn);
	free(tabn);
	free(rows);
	return 0;
}
