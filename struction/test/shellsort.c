#include <stdio.h>

void display(int* arr, int len){
    int i = 0;
    for(i=0;i<len;i++)
        printf("%d,",arr[i]);
    printf("\b \n");
}

void shellsort(int* arr, int len){
	int step = 1, tmp;
	int i = 0, j = 0;

	while(len/3<step) step = step*3+1;

	while(step>=1){
		for(i=step; i<len; i++){
			tmp = arr[i];
			for(j=i; j>=0 && arr[j-step]>tmp; j-=step)
				arr[j] = arr[j-step];
			arr[j] = tmp;
		}
		step = step/3;
	}
}

void main(){
	int arr[5] = {4,2,3,1,5};
	shellsort(arr, 5);
	display(arr, 5);
}
