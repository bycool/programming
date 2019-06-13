#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0;i<len;i++)
        printf("[%d]",arr[i]);
    printf("\n");
}


void sortsub(int* arr, int i, int len){
	int child, tmp;
	for(;i*2+1<len; i=child){
		child = 2*i+1;
		if(child+1<len && arr[child+1]>arr[child])
			child++;
		if(arr[child] > arr[i]){
			tmp = arr[child];
			arr[child] = arr[i];
			arr[i] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int*  arr, int len){
	int i = 0, j = 0;
	int tmp = 0;

	for(i=len/2-1; i>=0; i--)
		sortsub(arr, i, len);

	for(i=len-1; i>=0; i--){
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		sortsub(arr, 0, i);
	}
}

void main(){
	int arr[5] = {3,4,5,2,1};
	heapsort(arr, 5);
	display(arr, 5);
}
