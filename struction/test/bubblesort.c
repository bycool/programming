#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void bubblesort(int* arr, int len){
	int i = 0, j =0;
	int tmp = 0;
	for(i=0; i<len; i++){
		for(j=0; j<len-1; j++){
			if(arr[j] > arr[j+1]){
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

void main(){
	int arr[5] = {3,1,5,4,2};
	bubblesort(arr, 5);
	display(arr, 5);
}
