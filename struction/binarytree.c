#include <stdio.h>
#include <stdlib.h>

typedef struct binode {
	int val;
	struct binode *left, *right;
}binode;

typedef struct bitree {
	binode *root;
}bitree;

binode* newbinode(int val){
	binode *new = (binode*)malloc(sizeof(binode));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

bitree* newbitree(){
	bitree *tree = (bitree*)malloc(sizeof(binode));
	tree->root = NULL;
	return tree;
}

void bitree_insert_binode(bitree* tree, binode *new){
	if(tree == NULL) return ;
	binode *pn = NULL;
	binode *tmp = tree->root;

	while(tmp){
		pn = tmp;
		if(new->val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	if(pn){
		if(new->val < pn->val)
			pn->left = new;
		else
			pn->right = new;
	}else{
		tree->root = new;
	}
}

binode* findmin(binode* root){
	binode* min = root;
	while(min->left)
		min = min->left;
	return min;
}

binode* bitree_delete_binode(binode* root, int val){
	if(root == NULL) return NULL;

	if(val < root->val){
		root->left = bitree_delete_binode(root, val);
	}else if(val > root->val){
		root->right = bitree_delete_binode(root, val);
	}else if(root->left && root->right){
		binode* dtmp = findmin(root->right);
		root->val = dtmp->val;
		root->right = bitree_delete_binode(root->right, root->val);
	}else{
		binode* dtmp = root;
		if(root->left) root = root->left;
		else if(root->right) root = root->right;
		free(dtmp);
	}
	return root;
}


void bitree_delete(bitree* tree, int val){
	if(tree == NULL) return ;

	bitree_delete_binode(tree->root, val);
}

void displaybinode(binode* root){
	if(root == NULL) return ;
	displaybinode(root->left);
	printf(".[%d]", root->val);
	displaybinode(root->right);
}

void displaybitree(bitree* tree){
	if(tree == NULL) return ;
	displaybinode(tree->root);
	printf("\n");
}

void destroybinode(binode* root){
	if(root == NULL) return ;
	destroybinode(root->left);
	destroybinode(root->right);
	printf("-[%d]", root->val);
}

void destroybitree(bitree* tree){
	if(tree == NULL) return ;
	destroybinode(tree->root);
	free(tree);
	printf("-[tree]\n");
}

void main(){
	binode* tmp = NULL;
	bitree* tree = newbitree();
	int arr[15] = {5,2,7,18,3,9,1,4,8,6,10,12,14,15,12};
	int i = 0;
	for(i=0; i<15; i++){
		tmp = newbinode(arr[i]);
		bitree_insert_binode(tree, tmp);
	}

	displaybitree(tree);

	destroybitree(tree);
	
}







