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

bnode* btree_delete_bnode(bnode* root, int val){
	if(root == NULL) return ;

	if(val < root->val){
		root->left = btree_delete_bnode(root->left, val);
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
		free(tmp);
	}
	return root;
}

void btree_delete(btree* tree, int val){
	if(tree == NULL) return ;
	bnode* root = tree->root;
	btree_delete_bnode(root, val);
}

void ldr_displaybnode(bnode* root){
	if(root == NULL) return ;
	ldr_displaybnode(root->left);
	printf(".[%d]", root->val);
	ldr_displaybnode(root->right);
}

void ldr_displaybtree(btree* tree){
	if(tree == NULL) return ;
	ldr_displaybnode(tree->root);
	printf("\n");
}

void destorybnode(bnode* root){
	if(root == NULL) return ;
	destorybnode(root->left);
	destorybnode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destorybtree(btree* tree){
	if(tree == NULL) return ;
	destorybnode(tree->root);
	free(tree);
	printf("[-tree]\n");
}

void main(){
	int arr[10] = {5,2,4,9,6,1,0,3,8,7};
	int i = 0;
	btree* tree = newbtree();
	bnode* new = NULL;
	for(i=0; i<10; i++){
		new = newbnode(arr[i]);
		btree_insert_bnode(tree, new);
	}

	ldr_displaybtree(tree);

	btree_delete(tree, 9);

	ldr_displaybtree(tree);

	destorybtree(tree);
}

