#include <stdio.h>

void bubblesort(int* arr, int len){
	int i = 0, j = 0;
	int tmp = 0;
	for(i=0; i<len; i++){
		for(j=1; j<len; j++){
			if(arr[j-1] > arr[j]){
				tmp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = tmp;
			}
		}
	}
}

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void main(){
	int arr[10] = {5,2,8,1,0,4,3,6,9,7};
	bubblesort(arr, 10);
	display(arr, 10);
}
