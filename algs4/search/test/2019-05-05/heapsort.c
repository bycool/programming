#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void sortree(int* arr, int i, int len){
	int child, t;

	for(;2*i+1<len; i=child){
		child = 2*i+1;
		if(child+1<len && arr[child+1] >= arr[child])
			child++;
		if(arr[i] < arr[child]){
			t = arr[i];
			arr[i] = arr[child];
			arr[child] = t;
		}else{
			break;
		}
	}
}

void heapsort(int* arr, int len){
	int i = 0, t;

	for(i=len/2-1; i>=0; i--)
		sortree(arr, i, len);

	for(i=len-1; i>=0; i--){
		t = arr[i];
		arr[i] = arr[0];
		arr[0] = t;
		sortree(arr, 0, i);
	}
}

void main(){
	int arr[13]={9,2,6,8,5,10,4,7,3,13,12,11,1};
	heapsort(arr, 13);
	display(arr, 13);
}
