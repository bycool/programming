#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN 3

struct metime {
	int day;
	int year;
};

static struct metime** startime = NULL;

int main(){
	int i = 0;
	startime = (struct metime**)malloc(ARRAY_LEN * (sizeof(struct metime*)));
	if(!startime){
		printf("malloc size: %d fail\n", ARRAY_LEN * (sizeof(struct metime*)));
		return -1;
	}

	for(i=0; i<ARRAY_LEN; i++){
		startime[i] = (struct metime*)malloc(sizeof(struct metime));
		startime[i]->day = i;
		startime[i]->year = i+2018;

		printf("startime[%d].day = %d\n", i, i);
		printf("startime[%d].year = %d\n", i, i+2018);
		printf("----------------------------\n");
	}

	for(i=0; i<ARRAY_LEN; i++){
		free(startime[i]);
	}
	free(startime);
	
}
