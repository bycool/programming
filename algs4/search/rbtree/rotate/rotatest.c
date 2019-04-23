#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	int color;
	struct node *parent, *left, *right;
}node;

typedef struct Troot {
	node *root;
}Troot;

/*
 * 	  
    |                            |
    x                            y
 //   \\      对x进行左旋转    /   \
a      y                      x     c
    //   \\                  / \
   b       c                a   b

1:
   |
   x     y 
 /   \ /   \
a     b     c







*/


void left_rotate(Troot *root, node* x){
	node* y = x->right;

	x->right = y->left;
	if(y->left != NULL)
		y->left->right = x;

	
}



























void left_rotate(Troot *root, node* x){
	node* y = x->right;

	x->right = y->left;
	if(y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;

	if(x->parent == NULL){
		root->root = y;
	}else{
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
} 

