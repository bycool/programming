#include <stdio.h>
#include <stdlib.h>

typedef struct vnode {
	int val;
	struct vnode *pre, *next;
}vnode;

typedef struct stack {
	struct vnode *head, *tail;
	int len;
}stack;

vnode* newvnode(int val){
	vnode* new = (vnode*)malloc(sizeof(vnode));
	new->val = val;
	new->pre = NULL;
	new->next = NULL;
	return new;
}

stack* newstack(){
	stack *new = (stack*)malloc(sizeof(stack));
	new->head = NULL;
	new->tail = NULL;
	new->len = 0;
	return new;
}

int stack_push(stack* st, int val){
	if(st->len == 0){
		st->head = newvnode(val);
		st->tail = st->head;
		st->len = 1;
		return st->len;
	}

	vnode* new = newvnode(val);
	new->pre = st->tail;
	st->tail->next = new;
	st->tail = new;
	st->len += 1;
	return st->len;
}

int stack_pop(stack* st, int* pp){
	if(!st) return -1;
	if(st->len == 0){
		return -1;
	}
	vnode* dnode = st->tail;
	st->tail = st->tail->pre;
	st->tail->next = NULL;
	st->len -= 1;
	if(pp)
		*pp = dnode->val;
	free(dnode);
	return 0;
}

int stack_top(stack* st, int* tp){
	if(st->len == 0)
		return -1;

	if(!tp)
		return -1;
	else
		*tp = st->tail->val;
	return 0;
}

void display(stack* st){
	if(st->len == 0) return ;
	vnode* tmp = st->head;
	while(tmp){
		printf(".[%d]", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void destroy(stack* st){
	if(!st) return ;
	if(st->len == 0){
		free(st);
		return ;
	}
	vnode* tmp = st->head;
	vnode* dnode = NULL;
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
	stack* st = newstack();
	stack_push(st, 1);
	stack_push(st, 2);
	stack_push(st, 3);
	stack_push(st, 4);
	stack_push(st, 5);
	stack_push(st, 6);

	display(st);
	if(stack_pop(st, &rc)==0)
		printf("pop:%d\n", rc);
	rc = 0;
	display(st);

	if(stack_top(st, &rc)==0)
		printf("top:%d\n", rc);
	display(st);
	printf("size:%d\n", st->len);
	

	destroy(st);
}
