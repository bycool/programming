#include <stdio.h>
#include <stdlib.h>

#define HEIGHT(p) ( (p==NULL) ? 0 : (((anode*)(p))->height) )
#define MAX(a, b) ( (a)>(b) ? (a) : (b) )

typedef struct anode {
	int val;
	int height;
	struct anode *left, *right;
}anode;

anode* newanode(int val){
	anode* new = (anode*)malloc(sizeof(anode));
	new->val = val;
	new->height = 0;
	new->left = NULL;
	new->right = NULL;
	return new;
}
 
// LL
//              x
//             / \
//            y   c
//          /  \
//         a    b
//        /or\
//       d    e
anode* left_left_rotate(anode* x){
	anode* y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = MAX(HEIGHT(x->right), HEIGHT(x->left)) + 1;
	y->height = MAX(HEIGHT(y->left), x->height) + 1;

	return y;
}

//LR
//             x
//            / \
//           y   a
//          / \
//        b    c
//            /or\
//           d    e
anode* left_right_rotate(anode* x){
	x->left = right_right_rotate(x->left);
	return left_left_rotate(x);
}

//RL
//             x
//            / \
//           a   y
//              / \
//             b   c
//            /or\
//           d    e
anode* right_left_rotate(anode* x){
	x->right = left_left_rotate(x->right);
	return right_right_rotate(x);
}


//RR
//              x
//             / \
//            a   y
//               /  \
//              b    c
//                  /or\
//                 e    d
anode* right_right_rotate(anode* x){
	anode *y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), x->height) + 1;

	return y;
}


anode* avltree_insert(anode* root, anode* new){
	:
}











