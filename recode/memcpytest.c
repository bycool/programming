#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
	int num;
	char* str;
	int a;
};

int main(){
	struct node src;
	src.num = 1;
	src.str = (char*)malloc(10);
	strcpy(src.str, "123456");
	src.a = 2;

	printf("%d,%d,%s\n",src.num, src.a, src.str);

	char buf[10] = {0};
	struct node dst;
	dst.str = buf;

	memcpy(&dst, &src, sizeof(struct node));
	printf("%d,%d,%s,buf:%s\n",dst.num, dst.a, dst.str, buf);

	memcpy(dst.str, src.str, 10);
	printf("%d,%d,%s,buf:%s\n",dst.num, dst.a, dst.str, buf);
	
	

}
