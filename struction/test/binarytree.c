#include <stdio.h>
#include <stdlib.h>

typedef struct bnode {
	int val;
	struct bnode *left, *right;
}bnode;

bnode* newbnode(int val){
	bnode* new = (bnode*)malloc(sizeof(bnode));
	new->val = val;
	new->left = NULL;
	new->right = NULL;
	return new;
}

void btree_insert(bnode** root, int val){
	if(*root == NULL){
		*root = newbnode(val);
		return ;
	}

	if(val < (*root)->val){
		btree_insert(&((*root)->left), val);
	}else{
		btree_insert(&((*root)->right), val);
	}
}

void btree_insert_bnode(bnode** root, int val){
	bnode* pn = NULL;
	bnode* tmp = *root;
	bnode* new = NULL;

	while(tmp){
		pn = tmp;
		if(val < tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	new = newbnode(val);

	if(pn){
		if(val<pn->val)
			pn->left = new;
		else
			pn->right = new;
	}else{
		*root = new;
	}
}

bnode* findmin(bnode* root){
	if(root==NULL) return ;
	bnode* min = root;
	while(min->left)
		min = min->left;
	return min;
}

bnode* btree_delete(bnode* root, int val){
	if(root==NULL) return NULL;

	if(val<root->val){
		root->left = btree_delete(root->left, val);
	}else if(val>root->val){
		root->right = btree_delete(root->right, val);
	}else if(root->left && root->right){
		bnode* min = findmin(root->right);
		root->val = min->val;
		root->right = btree_delete(root->right, root->val);
	}else{
		bnode* dnode = root;
		if(root->left)
			root = root->left;
		else
			root = root->right;
		free(dnode);
	}
	return root;
}

void display(bnode* root){
	if(root== NULL) return ;

	display(root->left);
	printf("%d ", root->val);
	display(root->right);
}

void destory(bnode* root){
	if(root==NULL) return ;

	destory(root->left);
	destory(root->right);
	printf("-[%d]", root->val);
	free(root);
}

void main(){
	bnode* root = NULL;
	int arr[10] = {5,4,6,8,2,1,9,0,7,3};
	int i = 0;
	for(i=0; i<10; i++)
		btree_insert_bnode(&root, arr[i]);

	display(root);
	printf("\n");

	btree_delete(root, 1);

	display(root);
	printf("\n");

	destory(root);
	printf("\n");
}
