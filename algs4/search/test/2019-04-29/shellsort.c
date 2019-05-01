#include <stdio.h>

void display(int *arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d].", arr[i]);
	printf("\b \n");
}

void shellsort(int* arr, int len){
	int step=1, i, j, tmp;

	while(len/3 < step) step = step*3+1;

	while(step >= 1){
		for(i=step; i<len; i++){
			for(j=i; j>=step && arr[j-step] > arr[j]; j-=step){
				tmp = arr[j-step];
				arr[j-step] = arr[j];
				arr[j] = tmp;
			}
		}
		step = step/3;
	}
}

void main(){
	int arr[5] = {3,4,2,5,1};
	shellsort(arr, 5);
	display(arr, 5);
}
