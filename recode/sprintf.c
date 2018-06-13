#include <stdio.h>

int main(){
	char a[4] = {0};
	sprintf(a,"%s","1");
	sprintf(a,"%s%s",a,"2");
	printf("%s\n",a);
}
