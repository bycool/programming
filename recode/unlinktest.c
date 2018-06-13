#include <unistd.h>
#include <stdio.h>

int main(){
	int rc = unlink("1");
	printf("%d\n",rc);
}
