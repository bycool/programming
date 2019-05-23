#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int val;
	struct bnode *parent, *left, *right;
}bnode;

typedef struct btree {
	struct bnode* root;
}btree;


bnode* newbnode(int val){
	bnode* new = (bnode*)malloc(sizeof(bnode));
	new->val = val;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return new;
}

btree* newbtree(){
	btree* tree = (btree*)malloc(sizeof(btree));
	tree->root = NULL;
	return tree;
}

void btree_insert_bnode(btree *tree, bnode* new){
	if(tree == NULL) return ;

	bnode* pn = NULL;
	bnode* tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new->parent = pn;
	if(pn){
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}else{
		tree->root = new;
	}
}

bnode* findmin(bnode* root){
	if(root == NULL) return NULL;
	bnode* min = root;
	while(min->left)
		min = min->left;
	return min;
}

void btree_delete_bnode(rbnode* root, int val){
	if(root == NULL) return ;

	if(val < root->val){
		root->left = btree_delete_bnode(root->left, val)
	}else if(val > root->val){
		root->right = btree_delete_bnode(root->right, val);
	}else if(root->left && root->right){
		bnode* tmp = findmin(root->right);
		root->val = tmp->val;
		root->right = btree_delete_bnode(root->right, root->val);
	}else{
		bnode* tmp = root;
		if(root->left){
			root = root->left;
			root->left->parent = root->parent;
		}else{
			root = root->right;
			root->right->parent = root->parent;
		}
		free(tmp;
	}
	return root;
}


