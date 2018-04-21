#include <stdio.h>
#include <stdlib.h>

typedef struct dnode{
	int data;
	struct dnode* pre;
	struct dnode* next;
}node;

int initdlist(node** head, int data){
	if(*head != NULL ){
		printf("the head and tail is not null, if init, there will leak mem by head \n");
		return -1;
	}
	*head = (node*)malloc(sizeof(node));
	(*head)->data = data;
	(*head)->pre = NULL;
	(*head)->next = NULL;
	return 0;
}

int insertdlist(node** head, int offset ,int data){
	if(*head == NULL){
		printf("head is empty\n");
		return -1;
	}
}

int display(node** head){
	if(*head==NULL){
		printf("head is empty\n");
		return -1;
	}
	node* tmp = *head;
	while(tmp!=NULL){
		printf(".%d",tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
}

int destroydlist(node** head){
	if(*head == NULL ){
		printf("the dlist is empty\n");
		return -1;
	}
	node* tmp = *head;
	node* next = tmp;
	while(tmp!=NULL){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	//*head = NULL;
	return 0;
}


int main(){
	node* head = NULL;
	initdlist(&head,0);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	insertdlist(&head,1);
	display(&head);
	destroydlist(&head);
	display(&head);
}
