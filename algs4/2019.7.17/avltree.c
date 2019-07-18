#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b) )
#define HEIGHT(p) ((p==NULL) ? 0 : (((struct avlnode*)p)->height))

typedef struct avlnode {
	int val;
	int height;
	struct avlnode *left, *right;
}node;

node* newnode(int val) {
	node* new = (node*)malloc(sizeof(node));
	new->val = val;
	new->height = 0;
	new->left = NULL;
	new->right = NULL;
	return new;
}

//LL
//             x
//      y              c
// 	a      b
//d  e
node* left_left_rotate(node* x) {
	node* y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = MAX(HEIGHT(x->right), HEIGHT(x->left)) + 1;
	y->height = MAX(HEIGHT(y->right), HEIGHT(y->left)) + 1;

	return y;
}

//RR
//             x
//      c             y
//                 a      b
//                      d   e
node* right_right_rotate(node* x) {
	node* y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), HEIGHT(y->right)) + 1;

	return y;
}

//LR
//            x
//      y            c
//  a      b
//       d   e
node* left_right-rotate(node* x) {
	x->left = right_right_rotate(x->left);
	return left_left_rotate(x);
}

//RL
//            x
//     c             y
//               a       b
//             d  e
node* right_left_rotate(node* x) {
	x->right = left_left_rotate(x->right);
	return right_right_rotate(x);
}


