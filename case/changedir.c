#include <stdio.h>
#include <string.h>

//char reps[] = "/heha";
char rept[] = "/fdssdf/";
char reps[] = "/190613/";

void changedir(char* src_path, char* map_path, int level){
	if(level == 0) return ;
	char restname[1024] = {0};
	int i = 0;
	char* p = NULL;
	char* c = NULL;
	
	if(strstr(src_path, map_path)){
		p = src_path + strlen(map_path) - 1;
		c = p;
		printf("p: %s\n", p);
		for(i=0; i<level; i++){
			c = strchr(c, '/');
			c++;
			printf("c: %s\n", c);
		}
		c--;
		printf(".c: %s\n", c);
		p = strstr(c, reps);
		if(p==c){
			c = p +  strlen(reps);
			strcpy(restname, c);
			printf("restname: %s\n", restname);
			sprintf(p, "%s%s", rept, restname);
		}
	}
}

void main(){
	char map_path[] = "/home/ten/t1/";
	char src_path[] = "/home/ten/t1/190613/heha/nosjdijofwe";

	changedir(src_path, map_path, 1);

	printf("src_path: %s\n", src_path);

}
