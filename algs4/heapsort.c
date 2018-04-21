#include <stdio.h>

void heapadjust(int* arr,int i ,int length){
	int child;
	int tmp;
	for(;2*i+1<length;i=child){
		child = 2*i+1;
		if(2*i+1<length && arr[i]<arr[child]){
			++child;
		}
		if(arr[i]<arr[child]){
			tmp = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int * arr, int lenght){
	
}
