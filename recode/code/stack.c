#include <stdio.h>
#include <stdlib.h>

#define stack_size 3

typedef struct stack{
	int* top;
	int* base;
	int size;
}stack;

int initstack(stack* st){
	st->base = st->top = (int*)malloc(stack_size);
	st->size = 0;
	return 0;
}

int push(stack* st, int data){
	if(st->size >= stack_size){
		printf("stack is full\n");
		return st->size;
	}
	*(st->top) = data;
	(st->size)++;
	if(st->size < stack_size)
		(st->top)++;
	return st->size;
}

int pop(stack* st){
	if(st->size == 0){
		printf("stack is empty\n");
		return -1;
	}
	int ret = 0;
	if(st->size != stack_size)
		(st->top)--;
	ret = *(st->top);
	st->size--;
	return ret;
}

int display(stack* st){
	printf("st.size :%d\n",st->size);
	int* tmp = st->top;
	if(st->size < stack_size)
		tmp--;
	while((tmp)!=st->base){
		printf("%d\n",*tmp);
		tmp--;
	}
	printf("%d\n\n",*tmp);
	return 0;
}

int destroystack(stack* st){
	st->top = st->base;
	free(st->base);
	st->size=0;
	return 0;
}

int main(){
	stack st;
	initstack(&st);
	push(&st,1);
	push(&st,2);
	push(&st,3);
	push(&st,4);
	display(&st);
	int ret = pop(&st);
	printf("---pop:%d\n\n",ret);
	display(&st);
	printf("pop:%d\n",pop(&st));
	printf("pop:%d\n",pop(&st));
	printf("pop:%d\n",pop(&st));
	destroystack(&st);
}
