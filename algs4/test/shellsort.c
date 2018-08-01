#include <stdio.h>

void display(int* arr, int len ){
	int i = 0;
	for(i=0; i<len; i++)
		printf("%d,", arr[i]);
	printf("\b \n");
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 1 2 3 4 5 | 6 7 8 9 0
//                 i
//    j-s          j    

void shellsort(int* arr, int len){
	int step = 1;
	int i = 0, j = 0;
	int tmp = 0;

	while(len/3<step) step = step*3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			tmp = arr[i];
			for(j=i; arr[j-step]>tmp && j>=step; j-=step){
				arr[j] = arr[j-step];
			}
			arr[j]=tmp;
		}
		step = step/3;
	}
}

int main(){
	int arr[10] = {4,5,8,2,6,3,1,9,0,7};
	shellsort(arr, 10);
	display(arr, 10);
}
