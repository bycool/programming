#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* getnext(char* tgt){
	int i = 0, j = -1;
	int tl = strlen(tgt);

	int* next = (int*)malloc(sizeof(int)*(tl+1));
	next[0] = -1;

	while(i<tl){
		if(j==-1 || tgt[i]==tgt[j]){
			i++;
			j++;
			if(tgt[i]==tgt[j])
				next[i] = next[j];
			else
				next[i] = j;
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
		if(src[i]==tgt[j]){
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

	return -1;
}

void main(){
	char src[] = "sdfwefweffwegrgwefwefweff";
	char tgt[] = "fweffwe";

	int rc = kmp(src, tgt);
	printf("rc:%d\n", rc);
}
