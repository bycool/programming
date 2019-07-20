#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b) )
#define HEIGHT(p) ((p==NULL) ? 0 : (((struct avlnode*)p)->height))


typedef struct avlnode {
	int val;
	int height;
	struct avlnode *left, *right;
}node;

typedef struct avltree {
	struct avlnode* root;
}tree;

tree* newtree(){
	tree *new = (tree*)malloc(sizeof(tree));
	new->root = NULL;
	return new;
}

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
node* left_right_rotate(node* x) {
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

node* avlroot_insert_val(node* root, int val) {
	if(root == NULL){
		root = newnode(val);
	}else if(val < root->val){
		root->left = avlroot_insert_val(root->left, val);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2) {
			if(val < root->left->val)
				root = left_left_rotate(root);
			else
				root = left_right_rotate(root);
		}
	}else if(val > root->val){
		root->right = avlroot_insert_val(root->right, val);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2) {
			if(val < root->right->val)
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

void avltree_insert_node(tree* tree, int val) {
	if(tree == NULL) return ;
	tree->root = avlroot_insert_val(tree->root, val);
}

node* findmin(node* root) {
	node* min = root;
	while(min->left)
		min = min->left;
	return min;
}

node* findmax(node* root) {
	node* max = root;
	while(max->right)
		max = max->right;
	return max;
}



node* avlroot_delete_val(node* root, int val) {
	if(root == NULL) return  NULL;

	if(val < root->val){
		root->left = avlroot_delete_val(root->left, val);
		node* r = root->right;
		if(HEIGHT(r->left) > HEIGHT(r->right))
			root = right_left_rotate(root);
		else
			root = right_right_rotate(root);
	}else if(val > root->val) {
		root->right = avlroot_delete_val(root->right, val);
		node* l = root->left;
		if(HEIGHT(l->left) > HEIGHT(l->right))
			root = left_left_rotate(root);
		else
			root = left_right_rotate(root);
	}else if(root->left && root->right) {
		if(HEIGHT(root->left) > HEIGHT(root->right)){
			node* max = findmax(root->left);
			root->val = max->val;
			root->left = avlroot_delete_val(root->left, root->val);
		}else{
			node* min = findmin(root->right);
			root->val = min->val;
			root->right = avlroot_delete_val(root->right, root->val);
		}
	}else{
		node* dnode = root;
		if(root->left) root = root->left;
		else root = root->right;
		printf("-[%d|%d]\n", dnode->val, dnode->height);
		free(dnode);
	}
	return root;
}

void avltree_delete_node(tree* tree, int val) {
	if(tree == NULL) return ;
	tree->root = avlroot_delete_val(tree->root, val);
}


void destorynode(node* root){
	if(root == NULL) return ;
	destorynode(root->left);
	destorynode(root->right);
	printf("-[%d|%d]", root->val, root->height);
	free(root);
}

void destorytree(tree* tree) {
	if(tree == NULL) return ;
	destorynode(tree->root);
	printf("-[tree]\n");
	free(tree);
}

void ldr_displaynode(node* root){
	if(root == NULL) return ;
	ldr_displaynode(root->left);
	printf(".[%d|%d]", root->val, root->height);
	ldr_displaynode(root->right);
}

void ldr_displaytree(tree* tree){
	if(tree == NULL) return ;
	ldr_displaynode(tree->root);
	printf("\n");
}

void main () {
	tree* tree = newtree();

	int arr[16] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
	int i = 0;

	for(i=0; i<16; i++){
		avltree_insert_node(tree, arr[i]);
	}

	ldr_displaytree(tree);

	avltree_delete_node(tree, 15);

	ldr_displaytree(tree);
	destorytree(tree);
}

