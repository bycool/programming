#include <stdio.h>

#define LENGTH(p) ((sizeof(p)/(sizeof(p[0]))

static int heap[30];
static int heapsize = 30;
static int heaplen = 0;

int getindex(int val){
	int i = 0;
	for(i=0; i<heaplen; i++)
		if(heap[i] == val)
			return i;
	return -1;
}

static void minheap_fixdown(int start, int end){
	int c = start;
	int cv = heap[c];
	int l = 2*i+1;

	while(l<=end){
		if(l<end && heap[l] > heap[l+1])
			l++;
		else if(cv <= heap[l])
			break;
		else{
			heap[c] = heap[l];
			c = l;
			l = 2*l+1;
		}
	}
	heap[c] = cv;
}

int minheap_remove(int val){
	int index;

	if(heaplen == 0) return -1;

	index = getindex(val);
	if(index == -1) return -1;

	heap[index] = heap[--heaplen];
	minheap_fixdown(index, heaplen-1);

	return 0;
}

static void minheap_fixup(int start){
	int c = start;
	int cv = heap[c];
	int p = (c-1)/2;

	while(p>=0){
		if(p>0 && heap[p] <= cv)
			break;
		else{
			heap[c] = heap[p];
			c = p;
			p = (c-1)/2;
			
		}
	}
	heap[c] = cv;
}

int minheap_insert(int val){
	if(heaplen == heapsize) return -1;

	heap[heaplen++] = val;
	minheap_fixup(heaplen-1);

	return 0;
}

