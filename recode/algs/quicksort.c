#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b\n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;

	if(b>=e) return ;

	while(bb!=ee){
		while(arr[ee]>arr[b] && bb<ee)
			ee--;

		while(arr[bb]<arr[b] && bb<ee)
			bb++;

		if(bb<ee)
			swap(&arr[bb], &arr[ee]);
	}
	swap(&arr[bb], &arr[b]);
	quicksort(arr,b,bb);
	quicksort(arr,ee+1,e);
}

int main(){
	int arr[5] = {4,2,5,3,1};
	quicksort(arr, 0, 4);
	display(arr, 5);
}
