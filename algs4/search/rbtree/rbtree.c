#include <stdio.h>
#include <stdlib.h>

typedef struct rbnode {
	struct rbnode* parent;
	int val;
	int color;
	struct rbnode *left, *right;
}rbnode;

typedef struct Tnode {
	struct rbnode* root;
}Tnode;


/*     p             p
 *     x             y
 *  a     y       x    c
 *       b c     a b  
 */

void left_rotate(Tnode* root, rbnode* x){
	rbnode* y = x->right;

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
