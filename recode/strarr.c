#include <stdio.h>
#include <string.h>

typedef struct starr {
	int i;
	int j;
	int k;
}starr;

int main(){
    int i;
	starr sa[25];
	for(i=0;i<25;i++){
		sa[i].i = i;
		sa[i].j = i+1;
		sa[i].k = i+2;
	}

	memset(&sa[7], 0, sizeof(starr));

	for(i=0;i<25;i++){
		printf("::%d, i: %d, j: %d, k: %d\n", i, sa[i].i, sa[i].j, sa[i].k);
	}
	memset(sa, 0, sizeof(starr)*25);
}
