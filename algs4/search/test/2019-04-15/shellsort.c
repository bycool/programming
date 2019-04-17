#include <stdio.h>

void shellsort(int* arr, int len){
	int step=1, i=0, j=0, tmp;

	if(len/3>step) { step = 3*step+1; }

	while(step>=1){
		for(i=step; i<len; i++){
			for(j=i; j>=step && arr[j] <= arr[j-step]; j-=step){
				tmp = arr[j-step];
				arr[j-step] = arr[j];
				arr[j] = tmp;
			}
		}
		step = step/3;
	}
}

void display(int* arr,int len){
    int i =0;
    for(i=0;i<len;i++){
        printf("[%d]",arr[i]);
    }
    printf("\n");
}


int main(){
    int arr[13]={9,2,6,8,5,10,4,7,3,13,12,11,1};
    shellsort(arr,13);
    display(arr,13);
}

