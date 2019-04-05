#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
	int val;
	struct tnode *left, *right;
}tnode;

tnode* newtnode(int val){
	tnode *rc = (tnode*)malloc(sizeof(tnode));
	rc->val = val;
	rc->left = NULL;
	rc->right = NULL;
	return rc;
}

void insertotree(tnode** root, int val){
	tnode *tmpnode = NULL;

	if(*root == NULL){
		*root = newtnode(val);
		return ;
	}

	tmpnode = *root;
	if(val < tmpnode->val){
		if(tmpnode->left == NULL){
			tmpnode->left = newtnode(val);
		}else{
			insertotree(&(tmpnode->left), val);
		}
	}else{
		if(tmpnode->right == NULL){
			tmpnode->right = newtnode(val);
		}else{
			insertotree(&(tmpnode->right), val);
		}
	}
	return ;
}

tnode* searchnode(tnode* root, int val){
	if(root == NULL)
		return NULL;

	tnode *tmp = root;

	if(val < tmp->val){
		tmp = searchnode(tmp->left, val);
	}else if( val > tmp->val ){
		tmp = searchnode(tmp->right, val);
	}
	return tmp;
}


void midisplaytree(tnode* root){
	if(root == NULL)
		return;

	if(root->left != NULL)
		midisplaytree(root->left);

	printf("%d,", root->val);

	if(root->right != NULL)
		midisplaytree(root->right);
}

void destroytree(tnode* root){
	if(root == NULL)
		return;

	if(root->left != NULL)
		destroytree(root->left);

	if(root->right != NULL)
		destroytree(root->right);

	printf("[%d]", root->val);

	free(root);
	root = NULL;
}

tnode* findmin(tnode* root){
    if(root->left == NULL)
        return root;
    return findmin(root->left);
}

tnode* findmax(tnode* root){
    if(root->right == NULL)
        return root;
    return findmax(root->right);
}


tnode* deletenode(tnode* root, int val){
	if(root == NULL)
		return NULL;

	tnode* pnode = root;
	tnode* lcnode = NULL;

	if()

	
	
}


int main(){
	tnode* root = NULL;
	tnode* tmp = NULL;

	int arr[3] = {6,3,7};

	int i = 0;
	for(i=0; i<3; i++)
		insertotree(&root, arr[i]);
	midisplaytree(root);
	printf("\b \n");

	tmp = searchnode(root, 6);
	if(tmp){
		printf("%d\n", tmp->val);
		tmp->val = 100;
	}

	midisplaytree(root);
	printf("\b \n");

	tmp = findmin(root);
	printf("min: %d\n", tmp->val);

	tmp = findmax(root);
	printf("max: %d\n", tmp->val);

	destroytree(root);
	printf("\n");
	return 0;
}
