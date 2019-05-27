#include <stdio.h>

#define LENGHT(a) (sizeof((a))/sizeof((a[0]))

static int heap[30];
static int heapsize = 30;
static int heaplen = 0;

int getindex(int val){
	int i = 0;
	for(i=0; i<heaplen; i++){
		if(val == heap[i])
			return i;
	}
	return -1;
}


static void maxheap_fixdown(int start, int end){
	int c = start;
	int cv = heap[c];
	int l = 2*c+1;

	while(l<=end){
		if(l<end && heap[l] < heap[l+1])
			l++;
		else if(cv > heap[l])
			break;
		else{
			heap[c] = heap[l];
			c = l;
			l = 2*c+1;
		}
	}
	heap[c] = cv;
}

void maxheap_remove(int val){
	if(heaplen == ) return ;

	int index = getindex(val);
	if(index == -1)
		return -1;

	heap[index] = heap[--heaplen];
	maxheap_fixdown(index, heaplen-1);
}

static void maxheap_fixup(int start){
	int c = start;
	int p = (c-1)/2;
	int cv = heap[c];

	while(p>=0){
		if(cv < heap[p])
			break;
		else{
			heap[p] = heap[c];
			c = p;
			p = (c-1)/2;
		}
	}
	heap[c] = cv;
}

void maxheap_insert(int val){
	if(heaplen == heapsize)
		return ;

	heap[heaplen] = val;
	maxheap_fixup(heaplen);
	heaplen++;
}



