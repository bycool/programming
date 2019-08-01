#include <stdio.h>

void main() {
	int const a = 1;
	const int b = 2;
	int *p = &a;
	*p = 2;

	printf("a: %d\n", a);

}
