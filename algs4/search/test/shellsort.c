#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d].", arr[i]);
	printf("\b \n");
}

void shellsort(int* arr, int len){
	int step = 1, i, j;
	int tmp = 0;

	while(len/3 <step) step = step*3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			for(j=i; j>=step; j-=step){
				if(arr[j-step] > arr[j]){
					tmp = arr[j-step];
					arr[j-step] = arr[j];
					arr[j] = tmp;
				}else{
					break;
				}
			}
		}
		step = step/3;
	}
}


void main(){
	int arr[5] = {3,5,4,2,1};
	shellsort(arr, 5);
	display(arr, 5);
}
