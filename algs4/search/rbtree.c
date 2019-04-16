#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	int col;
	struct node *left, *right;
}rbnode;
