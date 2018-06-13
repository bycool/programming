#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

// 1,2,3,4,5  6,7,8,9,10  11,12,13,14,15

void shellsort(int* arr, int len){
	int i = 0, j = 0;
	int step = 1, tmp;
	while(step < len/3) step = 3*step + 1;
	while(step>=1){
//		printf("step: %d\n",step);
		for(i = step; i < len; i++){
//			printf("i:%d\n",i);
			for(j = i; j >= step && arr[j]<=arr[j-step] ; j = j - step){
			//	printf("arr[%d]: %d    arr[%d]: %d\n",j,arr[j],j-step,arr[j-step]);
			//	display(arr,len);
				tmp = arr[j];
				arr[j] = arr[j-step];
				arr[j-step] = tmp;
			}
		}
		step = step/3;
	}
}

int main(){
	int arr[15] = {7,8,4,5,2,1,3,4,8,0,9,11,12,15,14};
	shellsort(arr,15);
	display(arr,15);
}

