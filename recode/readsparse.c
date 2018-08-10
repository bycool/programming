#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	unsigned long i = 0;
	unsigned long cnt = 0;
	int fd = -1;
	char c = 0;
	struct stat fist;
	stat("./sparse.file",&fist);
	
	fd = open("./sparse.file", O_RDONLY, 0600);

	while(1){
		c = 0;
		read(fd, &c, 1);
		if(c=='1'){
			cnt++;
			printf("offset:%lu, cnt: %lu ,state: 1\n", i, cnt);
		}
		if(c=='2'){
			cnt++;
			printf("offset:%lu, cnt: %lu ,state: 2\n", i, cnt);
		}
		i++;
		if(cnt > fist.st_size)
			break;
		printf("%lu ",i);
	}
	printf("%lu\n",fist.st_size);

	close(fd);
	return 0;
}
