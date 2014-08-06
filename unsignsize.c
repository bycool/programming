#include <stdio.h>

main(){
	unsigned int a = 6;
	int  b = -20;
//	(a+b>6)?printf("%d\n",a):printf("%d\n",b);

	int c = 7;
	int d;
	d = a+++c;
//	printf("%d\n",d);

	typedef union {long i;int k[5];char c;} DATE; //union 8 || 20 || 1 = 20
	struct data {int cat; DATE cow; double dog;} too; //4 + 20 + 8 = 32
	DATE max;
	printf("%d\n",sizeof(struct data)+sizeof(max));  //32 +20
}
