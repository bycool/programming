#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct lnode{
	int data;
	struct lnode *pre,*next;
}node;

void insertlist(node** head,int a){
	if(*head == NULL ) return 0;
	node* p = *head;
	node* ins = (node*)malloc(sizeof(node));
	ins->data = a;
	(*head)->pre->next = ins;
	ins->next = *head;
	ins->pre  = (*head)->pre;
	(*head)->pre = ins ;
}

void print(node** head,int i){
	if(i==1){
		node *p = (*head)->next;
		while(p!=(*head)){
			printf("%d\n",p->data);
			p= p->next;
		};
	}else if(i==2){
		node *p = (*head)->pre;
		while(p!=(*head)){
			printf("%d\n",p->data);
			p=p->pre;
		}
		
	}
}


int main(){
	node* head=NULL;
	node* p = (node*)malloc(sizeof(node));
	head = p;
	p->pre = p;
	p->next = p;
	p->data = 0 ;

	insertlist(&p,2);
	insertlist(&p,3);
	insertlist(&p,4);
	insertlist(&p,5);
	insertlist(&p,6);
	insertlist(&p,7);
	insertlist(&p,8);
	insertlist(&p,9);
	insertlist(&p,10);
	insertlist(&p,11);
	insertlist(&p,12);
	insertlist(&p,13);
	insertlist(&p,14);



	print(&p,1);
	printf("-------------\n");
	print(&p,2);

}
