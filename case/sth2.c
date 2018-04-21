#include <stdio.h>

int main(){
	int i ;
	unsigned char a[4] = {1,2,3,4};
	for(i=0;i<4;i++){
		printf("%d,",a[i]);
	}
	printf("\nlen:%d\n",sizeof(a));

	printf("<<%d\n",a[0]<<24 | a[1]<<16 | a[2]<<8 | a[3] );

	return 0;
}
