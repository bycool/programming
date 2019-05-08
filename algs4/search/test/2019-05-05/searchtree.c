#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
	int val;
	struct snode *left, *right;
}snode;

typedef struct stree {
	struct snode *root;
}stree;

snode* newsnode(int val){
	snode* new = (snode*)malloc(sizeof(snode));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

stree* newstree(){
	stree* new = (stree*)malloc(sizeof(stree));
	new->root = NULL;
	return new;
}

void stree_insert_snode(stree* tree, snode* new){
	if(tree == NULL) return ;

	snode* pn = NULL;
	snode* tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if(pn == NULL){
		tree->root = new;
	}else{
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}
}

snode* findmin(snode* root){
	if(root == NULL) return NULL;

	snode* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

snode* stree_delete_snode(snode* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = stree_delete_snode(root->left, val);
	}else if(val > root->val){
		root->right = stree_delete_snode(root->right, val);
	}else if(root->left && root->right){
		snode* dnode = findmin(root->right);
		root->val = dnode->val;
		root->right = stree_delete_snode(root->right, root->val);
	}else{
		snode* dnode = root;
		if(root->left) root = root->left;
		else if(root->right) root = root->right;
		free(dnode);
	}
	return root;
}

void stree_delete(stree* tree, int val){
	if(tree == NULL) return ;
	stree_delete_snode(tree->root, val);
}

void ldr_displaysnode(snode* root){
	if(root == NULL) return ;
	ldr_displaysnode(root->left);
	printf(".[%d]", root->val);
	ldr_displaysnode(root->right);
}

void ldr_displaystree(stree* tree){
	if(tree == NULL) return ;
	ldr_displaysnode(tree->root);
	printf("\n");
}

void destroysnode(snode* root){
	if(root == NULL) return ;
	destroysnode(root->left);
	destroysnode(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void destroystree(stree* tree){
	if(tree == NULL) return ;
	destroysnode(tree->root);
	free(tree);
	printf("-[tree]\n");
}

void main(){
	int arr[10] = {3,7,3,5,1,2,8,9,0,4};
	int i = 0;
	stree* tree = NULL;
	snode* tmp = NULL;

	tree = newstree();
	for(i=0; i<10; i++){
		tmp = newsnode(arr[i]);
		stree_insert_snode(tree, tmp);
	}

	ldr_displaystree(tree);

	stree_delete(tree, 8);

	ldr_displaystree(tree);

	destroystree(tree);
}
