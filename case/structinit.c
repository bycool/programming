#include <stdio.h>

struct node {
	struct node* next;
	struct {
		int i;
		char* buf;
	}subnode;
	int j;
};

int main(){
	struct node head = {NULL,{0,"head"}};
	struct node second = {&head,{1,"second"}};
	printf("%d,%s\n",second.subnode.i,second.subnode.buf);
}
