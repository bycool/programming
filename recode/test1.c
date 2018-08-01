#include <unistd.h>

int main(){
	int rc = rmdir("./1");
	printf("%d\n",rc);
}
