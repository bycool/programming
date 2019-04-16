#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b>=e) return ;

	while(bb<ee){
		while(arr[ee] >= tmp && bb < ee)
			ee--;

		while(arr[bb] <= tmp && bb < ee)
			bb++;

		if(bb<ee)
			swap(&arr[bb], &arr[ee]);
	}

	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb);
	quicksort(arr, bb+1, e);
}


void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d],", arr[i]);
	printf("\b \n");
}

void main(){
	int arr[5] = {3,5,2,1,4};
	quicksort(arr, 0, 4);
	display(arr, 5);

}
