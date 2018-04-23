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
	node* tmp = *head;
	--offset;
	while(--offset && tmp->next != NULL){
			tmp = tmp->next;
	}
	if(offset!=0){
		printf("offset > list.len+1");
		return -1;
	}
	node* tnode = tmp->next;
	node* nnode = (node*)malloc(sizeof(node));
	nnode->data = data;
	nnode->pre = tmp;
	nnode->next = tnode;
	tmp->next = nnode;

	if(tnode!=NULL){
		tnode->pre = nnode;
	}
	return offset;
}

int insertdlistail(node** head, int data){
	node* tmp = *head;
	int i = 1;
	while(tmp->next!=NULL){
		tmp = tmp->next;
		i++;
	}
	tmp->next = (node*)malloc(sizeof(node));
	tmp->next->data = data;
	tmp->next->pre = tmp;
	tmp = tmp->next;
	tmp->next = NULL;
	return ++i;
}

int insertdlisthead(node** head, int data){
	node* tmp = *head;
	while(tmp->pre!=NULL){
		tmp = tmp->pre;
	}
	tmp->pre = (node*)malloc(sizeof(node));
	tmp->pre->data = data;
	tmp->pre->pre = NULL;
	tmp->pre->next = tmp;
	*head = tmp->pre;
	return 0;
}

int getlen(node** head){
	if(*head ==NULL)
		return 0;
	int cnt = 1;
	node* tmp = *head;
	while(tmp->next != NULL){
		tmp=tmp->next;
		cnt++;
	}
	return cnt;
}

int isemptylist(node** head){
	if(*head == NULL)
		return 1;
	return 0;
}

int getelem(node** head, int offset){
	if(offset > getlen(head)){
		printf("offset > list.len\n");
		return -1;
	}
	node* tmp = *head;
	while(--offset){
		tmp = tmp->next;
	}
	return tmp->data;
}

int locatelemflist(node** head,int data){
	int ret = -1;
	int offset = 1;
	node* tmp = *head;
	while(tmp!=NULL){
		if(tmp->data == data){
			ret = offset;
		}
		offset++;
		tmp = tmp->next;
	}
	return ret;
}

int removelemflist(node** head,int offset){
	if(offset>getlen(head)){
		printf("list[offset:%d] is not exist\n",offset);
		return -1;
	}
	node* tmp = *head;
	--offset;
	while(--offset && tmp->next!=NULL){
		tmp = tmp->next;
	}
	if(offset!=0 || tmp->next ==NULL){
		printf("offset > list.len +1 or tmp->next == NULL\n");
		return -1;
	}
	//tmp => offset-1;
	node* dnode = tmp->next;
	if(dnode->next == NULL){
		tmp->next = NULL;
	}else{
		tmp->next = dnode->next;
		dnode->next->pre = tmp;
	}
	offset = dnode->data;
	free(dnode);
	return offset;
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

int reverselist(node** head){
	if(getlen(head)<2){
		printf("list.len < 2\n");
		return -1;
	}
	node* pnode = *head;
	node* tmp = pnode->next;
	node* nnode = NULL;
	pnode->next = NULL;
	
	while(tmp!=NULL){
		nnode = tmp->next;
		pnode->pre = tmp;
		tmp->next = pnode;
		pnode = tmp;
		tmp = nnode;
	}
	*head = pnode;
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
	*head = NULL;
	return 0;
}


int main(){
	node* head = NULL;
	initdlist(&head,0);
	insertdlist(&head,2,1);
	insertdlist(&head,3,2);
	insertdlist(&head,4,3);
	insertdlist(&head,5,4);
	insertdlistail(&head,5);
	insertdlistail(&head,6);
	insertdlistail(&head,7);
	insertdlistail(&head,8);
	insertdlisthead(&head,-1);
	insertdlisthead(&head,-2);
	insertdlisthead(&head,-3);
	insertdlist(&head,3,99);
	display(&head);
	int ret = removelemflist(&head,13);
	printf("remove the 13 elem : %d\n",ret);
	display(&head);
	ret = removelemflist(&head,13);
	display(&head);
	int data = getelem(&head,5);
	printf("5th is %d\n",data);
	int loc = locatelemflist(&head,-1);
	printf("loc : %d\n",loc);
	
	printf("\n");
	display(&head);
	reverselist(&head);
	display(&head);

	

	destroydlist(&head);
	display(&head);
}

