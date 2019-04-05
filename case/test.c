#include <stdio.h>

typedef struct lnode {
	int i;
	int j;
	struct lnode *next;
}lnode;

void changeval(lnode* node, int i, int j){
	node->i = i;
	node->j = j;
}

void displaynode(lnode* node){
	printf("[%d|%d]\n", node->i, node->j);
}

int main(){
	lnode node;
	changeval(&node, 1, 2);
	displaynode(&node);
}
