#include <stdio.h>
#include <stdlib.h>

typedef struct lnode{
	int data;
	struct lnode* next;
}node;

int initlist(node** head,int data){
	if(*head != NULL){
		printf("head is not empty\n");
		return  -1;
	}
	*head = (node*)malloc(sizeof(node));
	(*head)->data=data;
	(*head)->next=NULL;
	return 0;
}

int display(node** head){
	if(*head==NULL){
		printf("the list is empty\n");
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

int isemptylist(node** head){
	if(*head == NULL)
		return 1;
	return 0;
}

int insertlisttail(node** head, int data){
	if(*head == NULL){
		printf("head is empty\n");
		return -1;
	}
	node* tmp = *head;
	while(tmp->next!=NULL){
		tmp = tmp->next;
	}
	node* nnode = (node*)malloc(sizeof(node));
	nnode->next = NULL;
	nnode->data = data;
	tmp->next = nnode;
	return 0;
}

int insertlisthead(node** head, int data){
	if(*head == NULL){
		printf("head is empty\n");
		return -1;
	}
	node* onode = *head;
	node* nnode = (node*)malloc(sizeof(node));
	nnode->next = onode;
	nnode->data = data;
	*head = nnode;
	return 0;
}

int createlistfarr(node** head, int*arr, int len){
	if(*head != NULL){
		printf("head is not empty\n");
		return -1;
	}
	node* tail = (node*)malloc(sizeof(node));
	tail->next = NULL;
	tail->data = arr[0];
	*head = tail;
	node* tmp = NULL;

	int i = 0;
	for(i=1;i<len;i++){
		tmp = (node*)malloc(sizeof(node));
		tmp->next = NULL;
		tmp->data = arr[i];
		tail->next = tmp;
		tail = tmp;
	}
	return 0;
}

int insertlistbyoffset(node** head, int offset ,int data){
	if(*head == NULL){
		printf("head empty\n");
		return -1;
	}
	node* tmp = *head;
	offset--;
	while(--offset && tmp->next!=NULL){
		tmp = tmp->next;
	}
	node* nnode = (node*)malloc(sizeof(node));
	nnode->data = data;
	nnode->next = tmp->next;
	tmp->next = nnode;
	return 0;
}

int getlen(node** head){
	if(*head == NULL)
		return 0;
	int cnt = 1;
	node* tmp = *head;
	while(tmp->next!=NULL){
		tmp = tmp->next;
		cnt++;
	}
	return cnt;
}

int getelem(node** head, int offset){
	if(*head ==NULL){
		printf("head is empty\n");
		return -1;
	}
	if(getlen(head)<offset){
		printf("offset > list.len\n");
		return -1;
	}
	node* tmp = *head;
	offset--;
	while(offset!=0){
		tmp = tmp->next;
		offset--;
	}
	return tmp->data;
}

int locatelem(node** head, int elem){
	int offset = 1;
	int ret = -1;
	node* tmp = *head;
	while(tmp!=NULL){
		if(tmp->data==elem){
			ret = offset;
			break;
		}
		tmp = tmp->next;
		offset++;
	}
	return ret;
	
}


int reverselist(node** head){
	if(getlen(head)<2){
		printf("less 2 elem cant reverse\n");
		return -1;
	}
	node* ntmp = NULL;
	node* ptmp = *head;
	node* tmp = ptmp->next;
	ptmp->next = NULL;
	while(tmp != NULL){
		ntmp = tmp->next;
		tmp->next = ptmp;
		ptmp = tmp;
		*head = ptmp;
		tmp = ntmp;
	}
	return 0;
}


int removelemflist(node** head,int offset){
	if(getlen(head)<offset){
		printf("elem[offset] is not excist\n");
		return -1;
	}
	node* tmp = *head;
	--offset;
	while(--offset){
		tmp = tmp->next;
	}
//	printf("%d\n",tmp->data);
	node* dnode = tmp->next;
	offset = dnode->data;
	tmp->next=dnode->next;
	free(dnode);
	return offset;
}

int destroylist(node** head){
	int cnt = 0;
	if(*head == NULL)
		return cnt;
	node* stmp = *head;
	node* ftmp = NULL;
	while(stmp != NULL){
		ftmp = stmp->next;
		free(stmp);
		stmp = ftmp;
		cnt++;
	}
	*head = NULL;
	return cnt;
}

int main(){
	node* head = NULL;
	initlist(&head,0);
	insertlisttail(&head,1);
	insertlisttail(&head,2);
	insertlisttail(&head,3);
	insertlisttail(&head,4);
	insertlisthead(&head,-1);
	insertlisthead(&head,-2);
	insertlistbyoffset(&head,4,99);
	display(&head);
	int ret = removelemflist(&head,4);
	printf("del elem is : %d\n",ret);
	display(&head);
	ret = removelemflist(&head,3);
	printf("del elem is : %d\n",ret);
	display(&head);
	int pos = getelem(&head,3);
	printf("list[3]:%d\n",pos);
	int locat = locatelem(&head,4);
	printf("locat: %d\n",locat);
	destroylist(&head);
	display(&head);

	int a[4] = {1,2,3,4};
	node* arrhead = NULL;
	createlistfarr(&arrhead,a,4);
	display(&arrhead);
	reverselist(&arrhead);
	display(&arrhead);
	

}
