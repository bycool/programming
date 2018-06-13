#include <stdio.h>
#include <stdlib.h>

typedef struct slnode{
	int data;
	struct slnode* next;
}node;


void display(node** head){
	node* tmp = *head;
	while(tmp!=NULL){
		printf("%d,",tmp->data);
		tmp = tmp->next;
	}
	printf("\b \n");
}

int main(){
	int arr[5] = {1,3,5,7,9};
	int brr[5] = {0,2,4,6,8};
	node* alist = (node*)malloc(sizeof(node)*5);
	node* blist = (node*)malloc(sizeof(node)*5);
	node* tmp = NULL;

	int i = 0;

	{
		for(i=0; i<5; i++){
			tmp = &alist[i];
			tmp->data = arr[i];
			tmp->next = &alist[i+1];
		}
		tmp->next = NULL;
	}
	{
		for(i=0; i<5; i++){
			tmp = &blist[i];
			tmp->data = brr[i];
			tmp->next = &blist[i+1];
		}
		tmp->next = NULL;
	}

	display(&alist);
	display(&blist);
}


