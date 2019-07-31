#include <stdio.h>

int vala;  //bss
int vala = 20;   //gcc会把这句认定为vala=20

f(int a){
	return 10;
}

void main() {
	printf("vala: %d\n", vala);
	int a = f();
	printf("f(): %d\n", a);
	a = f(1,2,3,4,5,6);
	printf("f(): %d\n", a);
}
