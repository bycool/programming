#include <stdio.h>

int vala;  //bss
int vala = 20;   //gcc会把这句认定为vala=20

void main() {
	printf("vala: %d\n", vala);
}
