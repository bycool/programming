#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node* parent;
	int val;
	int col;
	struct node *left, *right;
}rbnode;




