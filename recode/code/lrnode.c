#include <stdio.h>
#include <stdlib.h>

typedef struct lrnode{
	int data;
	struct lrnode* next;
}node;

int initlrlist(node** head,int data){
	if(*head != NULL){
		printf("head is not empty\n");
		return -1;
	}
	*head = (node*)malloc(sizeof(node));
	(*head)->data = data;
	(*head)->next = *head;
	return 0;
}

int insertlrlisttail(node** head, int data){
	if(*head == NULL){
		printf("list is empty\n");
		return -1;
	}
	node* tmp = *head;
	while(tmp->next!=(*head)){
		tmp = tmp->next;
	}
	node* nnode = (node*)malloc(sizeof(node));
	nnode->data = data;
	tmp->next = nnode;
	nnode->next = *head;

	return 0;
}

int getlen(node** head){
	if(*head==NULL)
		return 0;
	int cnt = 1;
	node* tmp = *head;
	while(tmp->next!=(*head)){
		tmp = tmp->next;
		cnt++;
	}
	return cnt;
}

int getelem(node** head, int offset){
	if(*head == NULL || offset>getlen(head)){
		printf("list is empty or offset > list.len\n");
		return -1;
	}
	node* tmp = *head;
	offset--;
	while(offset--){
		tmp = tmp->next;
	}
	int ret = tmp->data;
	return ret;
}

int locatelem(node** head, int data){
	int offset = 1;
	node* tmp = (*head);
	do{
		if(tmp->data == data)
			return offset;
		tmp = tmp->next;
		offset++;	
	}while(tmp!=*head);
	return -1;
}

int removelemflrlist(node** head, int offset){
	if(*head == NULL || offset > getlen(head)){
		printf("list empty or offset >list.len\n");
		return -1;
	}
	node* tmp = *head;
	node* dtmp = NULL;
	--offset;
	while(--offset){
		tmp = tmp->next;
	}
	dtmp = tmp->next;
	tmp->next = dtmp->next;
	int ret = dtmp->data;
	free(dtmp);
	return ret;
	
}

int display(node** head){
	if(*head == NULL){
		printf("list is emtpy\n");
		return -1;
	}
	node* tmp = *head;
	do{
		printf(".%d",tmp->data);
		tmp = tmp->next;
	}while(tmp!=*head);
	printf("\n");
	return 0;
}

int isempty(node** head){
	if(*head == NULL)
		return 1;
	return 0;
}

int reverselrlist(node** head){
	if(*head == NULL){
		printf("list is empty\n");
		return -1;
	}
	node* tmp = *head;
	node* next = tmp->next;
	node* nnext = next->next;
	while(next!=*head){
		next->next = tmp;
		tmp = next;
		next = nnext;
		nnext =nnext->next;
	}
	next->next = tmp;
	return 0;
}

int destroylrlist(node** head){
	if(*head == NULL){
		printf("list is empty,dont have to destroy\n");
		return -1;
	}
	node* tmp = (*head)->next;
	node* ntmp = tmp;
	while(tmp!=(*head)){
		ntmp = tmp->next;
		free(tmp);
		tmp = ntmp;
	}
	free(tmp);
	*head = NULL;
	return 0;
}

int main(){
	node* head = NULL;
	initlrlist(&head,0);
	printf("%d\n",locatelem(&head,0));
	insertlrlisttail(&head,1);
	printf("%d\n",locatelem(&head,1));
	insertlrlisttail(&head,2);
	printf("%d\n",locatelem(&head,6));
	insertlrlisttail(&head,3);
	insertlrlisttail(&head,4);
	insertlrlisttail(&head,5);
	insertlrlisttail(&head,6);
	display(&head);
	reverselrlist(&head);
	display(&head);
	int len = getlen(&head);
	printf("list.len: %d\n",getlen(&head));
	int elem = getelem(&head,3);
	printf("offset 3 elem is : %d\n",elem);
	int ret = removelemflrlist(&head,3);
	printf("remove elem.3 : %d\n",ret);
	display(&head);

	destroylrlist(&head);
}
