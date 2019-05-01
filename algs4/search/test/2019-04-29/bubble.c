#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d].", arr[i]);
	printf("\b \n");
}

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubblesort(int* arr, int len){
	int i, j;
	for(i=0; i<len; i++){
		for(j=1; j<len; j++){
			if(arr[j] < arr[j-1]){
				swap(&arr[j], &arr[j-1]);
			}
		}
	}
}

void main(){
	int arr[5] = {2,3,1,5,4};
	bubblesort(arr, 5);
	display(arr, 5);
}
