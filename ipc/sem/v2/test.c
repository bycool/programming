#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>

int main(){
	printf("%d",ftok(".",'s'));
	return 0;
}
