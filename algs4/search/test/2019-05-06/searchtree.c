#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int val;
	struct bnode *left, *right;
}bnode;

typedef struct btree {
	struct bnode *root;
}btree;

btree* creatree(){
	btree *tree = (btree*)malloc(sizeof(btree));
	tree->root = NULL;
	return tree;
}

bnode* newbnode(int val){
	bnode *new = (bnode*)malloc(sizeof(bnode));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void tree_insert_bnode(btree *tree, bnode *new){
	if(tree == NULL) return ;

	bnode *pn = NULL;
	bnode *tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if(new->val < pn->val)
		pn->left = new;
	else
		pn->right = new;
}

void tree_delete_bnode(btree *tree, int val){
	if(tree == NULL) return ;
}
