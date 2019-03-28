#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
	int val;
	struct lnode* next;
}lnode;


lnode* creatlist(int len){
	lnode* head = NULL;
	lnode* ptmp = NULL;
	lnode* tpmp = NULL;

	head = malloc(sizeof(lnode));
	head->val = 0;

	ptmp = head;
	len--;
	while(len--){
		tpmp = malloc(sizeof(lnode));
		tpmp->val = len;
		tpmp->next = NULL;
		ptmp->next = tpmp;
		ptmp = tpmp;		
	}

	return head;
}


void display(lnode* head){
	lnode* ptmp = head;
	while(ptmp != NULL){
		printf("%d,", ptmp->val);
		ptmp = ptmp->next;
	}
	printf("\n");
}

void destroylist(lnode* head){
	lnode* ptmp = head;
	lnode* tpmp = head;

	while(ptmp != NULL){
		tpmp = ptmp;
		ptmp = ptmp->next;
		free(tpmp);
	}
}

int getlenoflist(lnode* head){
	lnode* ptmp = head;
	int i = 0;
	while(ptmp!=NULL){
		i++;
		ptmp = ptmp->next;
	}
	return i;
}

void pushlist(lnode* head, int* array){
	lnode* ptmp = head;
	int i = 0;
	while(ptmp!=NULL){
		array[i] = ptmp->val;
		ptmp = ptmp->next;
		i++;
	}
}


int main(){
	lnode* head = creatlist(20);
	display(head);
	int len = getlenoflist(head);
	int* array = (int*)malloc(sizeof(int)*len);
	pushlist(head, array);
	while(len--){
		printf("%d ", array[len]);
	}
	printf("\n");
	destroylist(head);
	free(array);

	
}
