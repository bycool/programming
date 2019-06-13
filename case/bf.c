#include <stdio.h>

int bf(char* src, char* tgt){
	int i = 0, j = 0;
	int sl = strlen(src);
	int tl = strlen(tgt);

	while(i<sl && j<tl){
		if(src[i]==tgt[j]){
			i++;
			j++;
		}else{
			i = i-j+1;
			j=0;
		}
	}

	if(j==tl)
		return i-j;

	return -1;
}

void main(){
	char src[] = "awgergwfwefwgegw";
	char tgt[] = "fwef";

	int rc = bf(src, tgt);
	printf("rc : %d\n", rc);

}
