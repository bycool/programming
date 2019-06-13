#include <stdio.h>
#include <string.h>

int bf(char* src, char* tgt){
	int i = 0, j = 0;
	int sl = strlen(src);
	int tl = strlen(tgt);

	while(i<sl && j<tl){
		if(src[i]==tgt[j]){
			i++;
			j++;
		}else{
			i = i - j + 1;
			j = 0;
		}
	}

	if(tl==j)
		return i-j;

	return 0;
}

void main(){
	char src[] = "sdfwwgwwefwefw";
	char tgt[] = "gwwef";

	int rc = bf(src, tgt);
	printf("rc : %d\n", rc);
}
