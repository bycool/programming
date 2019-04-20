#include <stdio.h>
#include <stdlib.h>

typedef struct slnode{
	int data;
	struct slnode* next;
}node;

int insertslist(node** head, int data){
	int size = 1;
	node* newnode = (node*)malloc(sizeof(node));
	newnode->data = data;
	newnode->next = NULL;

	if(*head == NULL){
		*head = newnode;
	}else{
		node* tmp = *head;
		while(tmp->next!=NULL){
			tmp = tmp->next;
			size++;
		}
		tmp->next = newnode;
		size++;
	}
	return size;
}


int display(node** head){
	int size = 0;
	node* tmp = *head;
	while(tmp!=NULL){
		printf("%d,",tmp->data);
		tmp = tmp->next;
		size++;
	}
	printf("\b\tsize:%d\n",size);
	return size;
}


int destroyslist(node** head){
	if(*head==NULL){
		printf("slist is empty\n");
		return -1;
	}
	node* dtmp = *head;
	while(dtmp!=NULL){
		(*head) = dtmp->next;
		free(dtmp);
		dtmp = *head;
	}
	return 0;
}

int main(){
	node* head = NULL;
	insertslist(&head,0);
	insertslist(&head,2);
	insertslist(&head,1);
	insertslist(&head,3);
	insertslist(&head,5);
	display(&head);
	destroyslist(&head);
}
