#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* getnext(char* p){
	int pl = strlen(p);
	//printf("pl: %d\n", pl);
	int* next = (int*)malloc(pl*sizeof(int));
	next[0] = -1;

	int j = 0;
	int k = -1;

	while(j<pl){
	//	printf("p[%d]=%c, p[%d]=%c\n", k, p[k], j, p[j]);
		if(k==-1 || p[k] == p[j]){
			++j;
			++k;
			if(p[j]!=p[k])
				next[j] = k;
			else
				next[j] = next[k];
	//		printf("next[%d]= %d\n", j, k);
		}else{
			k = next[k];
		}
	}
	return next;
}

void display(int* next, int len){
	int i = 0;
	for(i=0; i<len; i++){
		printf("[%d]", next[i]);
	}
	printf("\n");
}

int kmp(char* src, char* tgt){
	int sl = strlen(src);
	int tl = strlen(tgt);

	int* next = getnext(tgt);

	display(next, tl);

	int i = 0, j = 0;

	while(j<tl && i<sl){
		if(src[i] == tgt[j]){
			i++;
			j++;
		}else{
			j = next[j];
			if(j==-1){
				i++; j++;
			}
		}
	}
	free(next);
	if(tl==j)
		return i-j;
	else
		return -1;
}


int main(){
	char src[] = {"abcdebabcdefgcfgabdeg"};
	char tgt[] = {"gcfgabde"};
	int p = kmp(src, tgt);
	printf("p: %d\n", p);
}
