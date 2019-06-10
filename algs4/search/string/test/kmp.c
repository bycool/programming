#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* getnext(char* p){
	int i = 0, j = -1;
	int pl = strlen(p);
	int* next = (int*)malloc(sizeof(int)*pl);
	next[0] = -1;

	while(i<pl){
		if(j==-1 || p[i] == p[j]){
			i++;
			j++;
			if(p[i] == p[j]){
				next[i] = next[j];
			}else{
				next[i] = j;
			}
		}else{
			j = next[j];
		}
	}

	return next;
}

int kmp(char* src, char* tgt){
	int i = 0, j = 0;
	int sl = strlen(src);
	int tl = strlen(tgt);

	int* next = getnext(tgt);

	while(i<sl && j<tl){
		if(src[i] == tgt[j]){
			i++;
			j++;
		}else{
			j = next[j];
			if(j==-1){
				i++;
				j++;
			}
		}
	}

	free(next);

	if(j==tl)
		return i-j;
	else
		return -1;
}

void main(){
	char src[] = "sdjfowiejnfosndsdfwefafwesdfsdwfsdfwe";
    char tgt[] = "fwefafwesdf";

	int rc = kmp(src, tgt);
	printf("rc = %d\n", rc);
}
