#include<stdio.h>
#include<stdlib.h>

struct Lnode
{
	int data;
	struct Lnode *next;
};

void print(struct Lnode *head)
{
	struct Lnode* p;
	p = head;
	while(p != NULL){
		printf("%d, ",p->data);
		p = p->next;
	}
	printf("\n");
}

struct Lnode *creat()
{
	struct Lnode *head,*p,*rear;
	int input = 0;
	head = (struct Lnode*)malloc(sizeof(struct Lnode));
	rear = head;
	puts("input a number, endwith -1:");
	scanf("%d",&input);
	while(input+1){
		p = (struct Lnode*)malloc(sizeof(struct Lnode));
		p->data = input;
		rear->next = p;
		rear = p;
		scanf("%d",&input);
	}
	rear->next = NULL;
	puts("the list is :");
	print(head->next);
	return head->next;
}

struct Lnode* reve(struct Lnode* head){
	struct Lnode * pre,*tmp,*next;
	pre = head;
	tmp = pre->next;
	pre->next = NULL;
	while(tmp->next != NULL){
		next = tmp->next;
		tmp->next = pre;
		pre = tmp;
		tmp = next;
	}
	tmp->next = pre;
	return tmp;
}

void main ()
{ 
	struct Lnode *head,*rev;
	head = creat();
	rev = reve(head);
	print(rev);
}
