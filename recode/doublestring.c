#include <string.h>

int main(){
	char args[5][1024]= {"111111", "2222222222", "3333333", "444444444"};
	printf("%s\n", args[0]);
	printf("%s\n", args[1]);
	printf("%s\n", args[2]);
	printf("%s\n", args[3]);

	strcpy(args[0],"777777777777777");
	sprintf(args[1],"888888888888");
	printf("%s\n", args[0]);
	printf("%s\n", args[1]);
}
