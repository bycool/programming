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

node* broot_delete_val(node* root, int val) {
	if(root == NULL) return ;

	if(val < root->val) {
		root->left = broot_delete_val(root->left, val);
	}else if(val > root->val) {
		root->right = broot_delete_val(root->right, val);
	}else if(root->left && root->right) {
		node* min = findmin(root->right);
		root->val = min->val;
		root->right = broot_delete_val(root->right, root->val);
	}else{
		node* dnode = root;
		if(root->left) root = root->left;
		else root = root->right;
		printf("-[%d]\n", dnode->val);
		free(dnode);
	}
	return root;
}

void btree_delete_val(btree* tree, int val) {
	if(tree == NULL) return ;
	broot_delete_val(tree->root, val);
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

	btree_delete_val(tree, 4);
	
	ldr_display(tree);

	destorytree(tree);
	
}


