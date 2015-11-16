#include<stdio.h>
#include<stdlib.h>
struct LNode
{
	int data;
	struct LNode *next;
};
struct LNode *creat();
void print (struct LNode *head,char a);
void main ()
{ 
	struct LNode *head;
	head = creat();
}
struct LNode *creat()
{
	struct LNode *head,*p,*rear;
	int x;
	char a;
	head=(struct LNode *)malloc(sizeof(struct LNode));
	rear=head;
	puts("input name of the list :\n");
	scanf("%c",&a);
	puts("input the list end with '-1':\n");
	scanf("%d",&x);
	while(x+1)
	{
		p=(struct LNode *)malloc(sizeof(struct LNode));
		p->data=x;
		rear->next=p;
		rear=p;
		scanf("%d",&x);
	}
	rear->next=NULL;
	puts("the list you input is :");
	print(head->next,a);
	return head->next;
}
void print (struct LNode *head,char a)
{
	struct LNode *p;
	p=head;
	printf("%c = ( ",a);
	while( p )
	{
		printf("%d ",p->data);
		p=p->next;
	}
	puts(")");
}
