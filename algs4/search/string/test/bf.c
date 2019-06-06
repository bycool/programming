#include <stdio.h>
#include <string.h>

int bf(char* src, char* tgt){
	int sl = strlen(src);
	int tl = strlen(tgt);

	int i = 0, j = 0;

	while(j<tl && i<sl){
		if(src[i] == tgt[j]){
			i++; j++;
		}else{
			i = i-j+1;
			j = 0;
		}
	}

	if(j==tl)
		return i-j;
	else
		return -1;
}

void main(){
	char src[] = "sdjfowiejnfosndsdfwefafwesdfsdwfsdfwe";
	char tgt[] = "fwefafwesdf";

	int rc = bf(src, tgt);
	printf("rc = %d\n", rc);
}
