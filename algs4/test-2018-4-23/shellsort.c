#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\n");
}

// 0,1,2,3,4 | 5,6,7,8,9 | 10,11,12,13,14


void shellsort(int* arr, int len){
	int i = 0, j=0, step = 0, tmp = 0;
	step = len/2;
	while(step>=1){
		for(i=step;i<len;i++){
			for(j=i; j>=step && arr[j]<arr[j-step];j=j-step){
				tmp = arr[j];
				arr[j] = arr[j-step];
				arr[j-step] = tmp;
			}
		}
		step = step/2;
	}
}

int main(){
	int arr[15] = {6,2,11,12,5,3,4,14,9,7,1,10,8,13,0};
	shellsort(arr,15);
	display(arr,15);
}


