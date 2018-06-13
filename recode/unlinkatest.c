#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int rc = unlinkat(AT_FDCWD,"1",AT_REMOVEDIR);
	printf("%d\n",rc);
}
