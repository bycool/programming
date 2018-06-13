#include <stdio.h>

typedef struct node{
	struct node* next;
	int a;
	int b;
	struct node* prev;
}node;

int main(){
	int i = 0;
	node tmp = {NULL,1,2,NULL};
	printf("%p\n",&i);
	printf("%p\n",&tmp);
	printf("%p\n",&(tmp.next));
	printf("%p\n",&(tmp.a));
	printf("%p\n",&(tmp.b));
	printf("%p\n",&(tmp.prev));
}
