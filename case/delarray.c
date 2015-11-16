#include <stdio.h>
#include <stdlib.h>

struct lnode{
	int date;
	struct lnode* next;
};

struct lnode* create(){
	struct lnode* head,*p,*rear;
	int input;
	head = (struct lnode*)malloc(sizeof(struct lnode));
	rear = head;
	puts("inpunt numbers, ends whit -1:");
	scanf("%d",&input);
	while(input+1){
		p = (struct lnode*)malloc(sizeof(struct lnode));
		p->date = input;
		rear->next = p;
		rear = p;
		scanf("%d",&input);
	}
	rear->next = NULL;
	return head->next;
}

void print(struct lnode* head){
	struct lnode* p;
	p = head;
	while(p != NULL){
		printf("%d\t",p->date);
		p = p->next;
	}
	printf("\n");
}

void delnode(struct lnode *p){
	struct lnode* pt;
	pt = p->next;
	p->date = pt->date;
	p->next = pt->next;
	free(pt);
}

main(){
	struct lnode* head = create();
	print(head);
	struct lnode* del = head->next;
	delnode(del);
	print(head);
}

