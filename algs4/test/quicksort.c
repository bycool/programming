#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 1 2 3 4 5
// b       e
// bb      ee

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b];

	if(b>e) return;

	while(bb!=ee){
		while(arr[ee] >= tmp && bb < ee)
			ee--;
		while(arr[bb] <= tmp && bb < ee)
			bb++;
		if(bb<ee)
			swap(&arr[ee], &arr[bb]);
	}
	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb-1);
	quicksort(arr, bb+1, e);
}

int main(){
	int arr[5] = {4,2,3,1,5};
	quicksort(arr, 0, 4);
	display(arr, 5);
}
