#include <stdio.h>
#include <stdlib.h>

typedef struct lnode {
	int i;
	struct lnode* next;
}node;



//-1->0->1->2->3->4->5->6->7->8->9->6
node* createlistrang(){
	node* head = (node*)malloc(sizeof(node));
	head->i = -1;
	node* tmp = head;
	node* ntmp = NULL;
	node* rtmp = NULL;
	int i = 0;
	for(i=0;i<10;i++){
		ntmp = (node*)malloc(sizeof(node));
		ntmp->i = i;
		if(i==6)
			rtmp = ntmp;
		tmp->next = ntmp;
		ntmp->next = NULL;
		tmp = ntmp;
	}
	tmp->next = rtmp;
	return head;
}

int checkrang(node* head){
	node* slow = head;
	node* fast = head;
	while(slow!=NULL && fast!=NULL){
		slow = slow->next;
		fast = fast->next;
		fast = fast->next;
		if(slow==fast){
			printf("get a rang\n");
			return 1;
		}
	}
	printf("none of rang\n");
	return 0;
}

void display(node* head){
	node* tmp = head;
	while(tmp!= NULL){
		printf("i:%d\n",tmp->i);
		tmp = tmp->next;
	}
}

int main(){
	node* head = createlistrang();
	checkrang(head);

}
