#include <stdio.h>
#include <stdlib.h>

#define HEIGHT(p) ( (p==NULL) ? 0 : ((node*)(p)->height) )
#define MAX(a, b) ( ((a)>(b)) ? (a) : (b) )

typedef struct node {
	int val;
	int height;
	struct node *left, *right;
}node;

typedef struct tree {
	struct node *root;
}tree;


node* newnode(int val){
	node* new = (node*)malloc(sizeof(node));
	new->val = val;
	new->height = 0;
	new->left = NULL;
	new->right = NULL;
	return new;
}

tree* newtree(){
	tree* new = (tree*)malloc(sizeof(tree));
	new->root = NULL;
	return new;
}

//LL              x
//            y       a
//        z      b
//      c   d
node* left_left_rotate(node* x){
	node *y = x->left;
	x->left = y->right;
	y->right = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), HEIGHT(y->right)) + 1;

	return y;
}

//RR     x
//   a        y
//       b         z
//               c   d
node* right_right_rotate(node* x){
	node* y = x->right;
	x->right = y->left;
	y->left = x;

	x->height = MAX(HEIGHT(x->left), HEIGHT(x->right)) + 1;
	y->height = MAX(HEIGHT(y->left), HEIGHT(y->right)) + 1;

	return y;
}

//LR             x
//          y       a
//       b     z
//           c   d
node* left_right_rotate(node* x){
	x->left = right_right_rotate(x->left);
	return left_left_rotate(x);
}

//RL       x
//    a          y
//           z        b
//         c   d
node* right_left_rotate(node* x){
	x->right = left_left_rotate(x->right);
	return right_right_rotate(x);
}


node* avltree_insert(node* root, int val){
	if(root == NULL){
		root = newnode(val);
	}else if(val < root->val){
		root->left = avltree_insert(root->left, val):
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2){
			if(val < root->left->val)
				root = left_left_rotate(root);
			else
				root = left_right_rotate(root);
		}
	}else if(val > root->val){
		root->right = avltree_insert(root->right, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2){
			if(val <root->right)
				root = right_left_rotate(root);
			else
				root = right_right_rotate(root);
		}
	}else{
		printf("same val\n");
	}

	root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;

	return root;
} 

node* findmin(node* root){
	if(root==NULL) return NULL;
	node* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

node* findmax(node* root){
	if(root==NULL) return NULL;
	node* tmp = root;
	while(tmp->right)
		tmp = tmp->right;
	return tmp;
}

node* avltree_delete(node* root, int val){
	if(val < root->val){
		root->left = avltree_delete(root->left, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2){
			node* r = root->right;
			if(HEIGHT(r->left) > HEIGHT(r->right))
				root = right_left_rotate(root);
			else
				root = right_right_rotate(root);
		}
	}else if(val > root->val){
		root->right = avltree_delete(root->right, val);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2){
			node* l = root->left;
			if(HEIGHT(l->left) > HEIGHT(l->right))
				root = left_left_rotate(root);
			else
				root = left_right_rotate(root);
		}
	}else if(root->left && root->right){
		if(HEIGHT(root->left) > HEIGHT(root->right)){
			node* max = findmax(root->left);
			root->val = max->val;
			root->left = avltree_delete(root->left, root->val);
		}else{
			node* min = findmin(root->right);
			root->val = min->val;
			root->right = avltree_delete(root->right, root->val);
		}
	}else{
		node* d = root;
		if(root->left)
			root = root->left;
		else
			root = root->right;
		free(d);
	}

	return root;
}






