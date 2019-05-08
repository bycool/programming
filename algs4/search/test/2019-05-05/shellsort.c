#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void shellsort(int* arr, int len){
	int step = 1;
	int i = 0, j = 0;
	int t = 0;

	while(len/3>step) step = step*3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			for(j=i; j>=step && arr[j-step]>arr[j]; j-=step){
				t = arr[j];
				arr[j] = arr[j-step];
				arr[j-step] = t;
			}
		}
		step = step/3;
	}
}

void main(){
	int arr[15] = {5,7,2,1,8,12,14,13,15,11,9,4,3,10,6} ;
	shellsort(arr, 15);
	display(arr, 15);
}
