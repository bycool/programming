#include <stdio.h>

typedef struct node{
	int i;
	int j;
}node;

int main(){
	node n1 = {1,2};
	printf("%d, %d\n",n1.i, n1.j);
	node* pn1 = &n1;
	printf("%d, %d\n",pn1->i,pn1->j);

	int i = 1;
	int* pi = &i;
	printf("%d\n",*pi);
}
