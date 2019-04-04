#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* lnode;
	struct node* rnode;
}Tnode;

Tnode* creatree(){
	Tnode* rootnode;
	int input;
	rootnode = (Tnode*)malloc(sizeof(Tnode));
	printf("input a number:\n");
	scanf("%d",&input);
	rootnode->data = input;
	rootnode->lnode = NULL;
	rootnode->rnode = NULL;
	return rootnode;
}


/*
 * 有序插入（左小右大）
 */
void insertree(Tnode* node,int i){
	if(node == NULL)
		return;
	Tnode* tmp = (Tnode*)malloc(sizeof(Tnode));
	tmp->data = i;
	tmp->lnode = NULL;
	tmp->rnode = NULL;
	if(node->data < i){
		if(node->rnode == NULL){
			node->rnode = tmp;
		}else{
			free(tmp);
			insertree(node->rnode,i);
		}
	}else if(node->data >=i){
		if(node->lnode == NULL){
			node->lnode = tmp;
		}else{
			free(tmp);
			insertree(node->lnode,i);
		}
	}
}

/*
 * 先序遍历(根左右)
 */
void preprintree(Tnode *node){
	if(node != NULL)
		printf("%d  ",node->data);
	if(node->lnode != NULL)
		preprintree(node->lnode);
	if(node->rnode != NULL)
		preprintree(node->rnode);
	return ;
}

/*
 * 后序遍历(左右根)
 */
void backprintree(Tnode *node){
	if(node->lnode != NULL)
		backprintree(node->lnode);
	if(node->rnode != NULL)
		backprintree(node->rnode);
	if(node != NULL) 
		printf("%d  ",node->data);
	return ;
}

/*
 * 中序遍历(左根右)
 */
void midprintree(Tnode *node){
	if(node->lnode != NULL)
		midprintree(node->lnode);
	if(node != NULL)
		printf("%d  ",node->data);
	if(node->rnode != NULL)
		midprintree(node->rnode);
	return ;
}

int main(){
	Tnode* rootnode = creatree();
	insertree(rootnode,2);
	insertree(rootnode,10);
	insertree(rootnode,5);
	insertree(rootnode,9);
	insertree(rootnode,4);
	insertree(rootnode,7);
	insertree(rootnode,6);
	insertree(rootnode,8);
	insertree(rootnode,11);
	insertree(rootnode,3);
	insertree(rootnode,12);
//	backprintree(rootnode);
	midprintree(rootnode);
	printf("\n");

	return 0;
}
