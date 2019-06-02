#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0; i<len; i++)
        printf("[%d],", arr[i]);
    printf("\b \n");
}

void sortree(int* arr, int i, int len){
	int child , tmp;
	for(;2*i+1<len; i=child){
		child = 2*i+1;
		if(child+1<len && arr[child] < arr[child+1]){
			child++;
		}

		if(arr[child] > arr[i]){
			tmp  = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int* arr, int len){
	int i = 0;
	int tmp;

	for(i=len/2-1; i>=0; i--)
		sortree(arr, i, len);

	for(i=len-1; i>=0; i--){
		sortree(arr, 0, i);
		tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
	}
}

void main(){
	int arr[5] = {3,2,4,1,5};
	heapsort(arr, 5);
	display(arr, 5);
}
