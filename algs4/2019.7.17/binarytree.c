#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int val;
	struct bnode *left, *right;
}node;

typedef struct btree {
	struct bnode *root;
}btree;

node* newnode(int val) {
	node* new = (node*)malloc(sizeof(node));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

btree* newtree(){
	btree* newtree = (btree*)malloc(sizeof(btree));
	newtree->root = NULL;
	return newtree;
}


void btree_insert_node(btree* tree, node* new) {
	if(tree == NULL) return ;

	node* tmp = tree->root;
	node* pn = NULL;

	while(tmp) {
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if(pn == NULL)
		tree->root = new;
	else{
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}
}

node* findmin(node* root) {
	node* min = NULL;

	
}

void btree_delete_val(btree* tree, int val) {
	
}


void ldr_displaynode(node* root){
	if(root == NULL) return ;
	ldr_displaynode(root->left);
	printf(".[%d]", root->val);
	ldr_displaynode(root->right);
}

void ldr_display(btree* tree){
	if(tree == NULL) return ;
	ldr_displaynode(tree->root);
	printf("\n");
}

void destorynode(node* root) {
	if(root==NULL) return ;
	destorynode(root->left);
	destorynode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destorytree(btree* tree) {
	if(tree == NULL) return ;
	destorynode(tree->root);
	printf("-[tree]\n", tree);
	free(tree);
}

void main() {
	int arr[10] = {7,8,5,9,2,4,1,3,6,0};
	btree* tree = newtree();
	node* new = NULL;

	int i = 0;
	for(i=0; i<10; i++) {
		new = newnode(arr[i]);
		btree_insert_node(tree, new);
	}

	ldr_display(tree);

	destorytree(tree);
	
}


