#include <stdio.h>

typedef struct node{
	int i;
    int j;
}node;

void printnode(node node){
	printf("node.i: %d\n",node.i);
	printf("node.j: %d\n",node.j);
}

void initnode(int* i, int* j){
	*i = 1;
    *j = 2;
}

int main(){
	node n;
	initnode(&n.i, &n.j);
	printnode(n);
}
