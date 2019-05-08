#include <stdio.h>
#include <string.h>

void main(){
	int rc = strlen("\\");
	printf("rc = %d\n", rc);

	rc = strlen("/");
	printf("rc = %d\n", rc);
}
