#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *left, *right;
}node;

/*
 * 生成新节点，返回指针
 */
node* newnode(int val){
	node* rc = (node*)malloc(sizeof(node));
	rc->val = val;
	rc->left = NULL;
	rc->right = NULL;
	return rc;
}

/*
 * 向节点插入新值
 */
void insertnode(node** root, int val){
	if(*root == NULL){
		*root = newnode(val);
		return;
	}

	if(val < (*root)->val)
		insertnode(&((*root)->left), val);
	else
		insertnode(&((*root)->right), val);
}

/*
 * 找出树内最小节点
 */
node* findmin(node* root){
	node* tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

/*
 * 找出树内最大节点
 */
node* findmax(node* root){
	node* tmp = root;
	while(tmp->right)
		tmp = tmp->right;
	return tmp;
}

/*
 * 删除树中节点
 */
node* deletenode(node* root, int val){
	if(root==NULL) return NULL;

	node* tmp = NULL;

	if(val < root->val){
		root->left = deletenode(root->left, val);
	}else if(val > root->val){
		root->right = deletenode(root->right, val);
	}else if(root->left && root->right){
		tmp = findmin(root->right);
		root->val = tmp->val;
		root->right = deletenode(root->right, root->val);
	}else{
		tmp = root;
		if(root->left == NULL) root = root->right;
		else if(root->right = NULL) root = root->left;
		free(tmp);
	}
	return root;
}


/*
 * 中序遍历
 */
void midisplay(node* root){
	if(root==NULL) return;
	midisplay(root->left);
	printf("[%d]", root->val);
	midisplay(root->right);
}

/*
 * 销毁树
 */
void destroytree(node* root){
	if(root==NULL) return;
	destroytree(root->left);
	destroytree(root->right);
	printf(".[%d]", root->val);
	free(root);
}


void main(){
	int i = 0;
	node* root = NULL;
	int arr[5] = {5,2,8,1,6};

	for(i=0; i<5; i++)
		insertnode(&root, arr[i]);

	node* tmp = NULL;
	tmp = findmin(root);
	printf("min:%d\n", tmp->val);
	tmp = findmax(root);
	printf("max:%d\n", tmp->val);

	deletenode(root, 6);

	midisplay(root);
	printf("\n");
	destroytree(root);
	printf("\n");
}



