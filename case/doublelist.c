#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct dlnode{
	int data;
	struct dlnode* pre,*next;
}node;

void initlist(node** head){
	if(*head==NULL){
		*head = (node*)malloc(sizeof(node));
		(*head)->data = 0;
		(*head)->next = (*head)->pre = (*head);
	}else{
		printf("the head of dlist has inited\n");
	}
}

void insertlist(node** head,int data){
	if(*head==NULL){
		printf("the list is empty,please init first\n");
		return ;
	}

	node* tmp = (node*)malloc(sizeof(node));
	tmp->data = data;
	(*head)->pre->next = tmp;
	tmp->next = (*head);
	tmp->pre = (*head)->pre;
	(*head)->pre = tmp;
	printf("new node data: [%d]\n",data);
}

void printlist(node** head,int order){
	if(*head==NULL){
		printf("the list is empty\n");
		return ;
	}
	if(order == 1){
		node* p = (*head)->next;
		while(p!=(*head)){
			printf("%d\n",p->data);
			p=p->next;
		}
	}else if(order==2){
		node* p = (*head)->pre;
		while(p!=(*head)){
			printf("%d\n",p->data);
			p=p->pre;
		}
	}
}

void dellist(node** head){
	if(*head==NULL){
		printf("the list is empty\n");
		return;
	}
	node* tmp = (*head)->next;
	while(tmp->next!=NULL){
		tmp->pre->next = NULL;
		printf("del:%d\n",tmp->data);
		tmp = tmp->next;
		free(tmp->pre);
	}
	printf("del:head %d\n",(*head)->data);
	free(*head);
	*head = NULL;
}

int main(){
	node* head = NULL;
	initlist(&head);
	printf("%d\n",head->data);
	insertlist(&head,1);
	insertlist(&head,2);
	insertlist(&head,3);
	insertlist(&head,4);
	printlist(&head,1);
	printf("-----------------\n");
	printlist(&head,2);

	dellist(&head);
	printlist(&head,2);

}
