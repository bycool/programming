#include <stdio.h>
#include <stdlib.h>

typedef struct qnode {
	int val;
	struct qnode *pre, *next;
}qnode;

typedef struct queue {
	int len;
	struct qnode *head, *tail;
}queue;

qnode* newqnode(int val){
	qnode* new = (qnode*)malloc(sizeof(qnode));
	new->val = val;
	new->pre = NULL;
	new->next = NULL;
	return new;
}

queue* newqueue(){
	queue* new = (queue*)malloc(sizeof(queue));
	new->len = 0;
	new->head = NULL;
	new->tail = NULL;
	return new;
}

int enqueue(queue* qu, int val){
	if(!qu) return -1;
	if(qu->len == 0){
		qu->head = newqnode(val);
		qu->tail = qu->head;
		qu->len = 1;
		return qu->len;
	}

	qnode* new = newqnode(val);
	new->pre = qu->tail;
	qu->tail->next = new;
	qu->tail = new;
	qu->len += 1;
	return qu->len;
}

int dequeue(queue* qu, int* val){
	if(!qu) return -1;
	if(qu->len == 0)
		return -1;
	qnode* dnode = qu->head;
	qu->head = qu->head->next;
	qu->head->pre = NULL;
	if(val)
		*val = dnode->val;
	free(dnode);
	return 0;
}
void display(queue* qu){
    if(qu->len == 0) return ;
    qnode* tmp = qu->head;
    while(tmp){
        printf(".[%d]", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}

void destroy(queue* qu){
    if(!qu) return ;
    if(qu->len == 0){
        free(qu);
        return ;
    }
    qnode* tmp = qu->head;
    qnode* dnode = NULL;
    while(tmp){
        dnode = tmp;
        printf("-[%d]", tmp->val);
        tmp = tmp->next;
        free(dnode);
    }
    printf("\n");
}

void main(){
	int rc = 0;
	queue *qu = newqueue();
	enqueue(qu, 1);
	enqueue(qu, 2);
	enqueue(qu, 3);
	enqueue(qu, 4);
	enqueue(qu, 5);

	display(qu);
	if(dequeue(qu, &rc) == 0)
		printf("de: %d\n", rc);

	display(qu);
	destroy(qu);
}
