#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int ret = 0;
	int i = 0;
	int idx = 0;
	int bufcnt = 0;
	int fd;
	char** buf = NULL;
	struct stat fst;

	bufcnt = argc-1;
	printf("bufcnt: %d\n", bufcnt);
	buf = (char**)malloc(sizeof(char*)*bufcnt);

	for(i=1; i<argc; i++) {
		fd = open(argv[i], O_RDONLY, 0600);
		if(fd < 0) {
			printf("open %s fail\n", argv[i]);
			return 0;
		}
		if(fstat(fd, &fst)==-1) {
			printf("fstat %s fail\n", argv[i]);
			close(fd);
			return 0;
		}
		printf("filename: %s, size: %u\n", argv[i], fst.st_size);
		buf[idx] = (char*)malloc(fst.st_size);
		ret = read(fd, buf[idx], fst.st_size);
		buf[idx][ret] = 0;
		if(ret != fst.st_size) {
			printf("read %s error [%d|%d]\n", argv[i], fst.st_size, ret);
			close(fd);
			return 0;
		}
		close(fd);
	//	printf("\n%s buf[%d]:\n%s", argv[i], idx, buf[idx]);
		idx++;
	}

printf("idx: %d\n", idx);
	for(i=0; i<idx; i++) {
		free(buf[idx]);
		printf("free buf[%d]\n", idx);
	//	buf[idx] = NULL;
	}
	return 0;
}
