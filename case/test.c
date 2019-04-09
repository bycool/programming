#include <stdio.h>
#include <stdlib.h>

#if 0
typedef struct lnode {
	int i;
	int j;
	struct lnode *next;
}lnode;

void changeval(lnode* node, int i, int j){
	node->i = i;
	node->j = j;
	lnode
}

void displaynode(lnode* node){
	printf("[%d|%d]\n", node->i, node->j);
}

int main(){
	lnode node;
	changeval(&node, 1, 2);
	displaynode(&node);
}
#endif

void getmem(int** arr, int len){
	int i = 0;
	*arr = (int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++)
		(*arr)[i] = i;
}

int main(){
	int* arr = NULL;
	getmem(&arr, 5);
	int i;
	for(i=0;i<5;i++)
		printf("%d,", arr[i]);
}
