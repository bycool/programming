#include <stdio.h>

void printarr(int* arr,int len){
    int i =0;
    for(i=0;i<len;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");
}



void shellsort(int* arr,int len){
	
	int i=0,j=0;
	int tmp;
	int step = len/2;
	while(step>=1){
		printf("step:%d\n",step);
		printarr(arr,13);
		for(i=step;i<len;i++){
			for(j=i;j>=step&&arr[j]<arr[j-step];j-=step){
				tmp = arr[j];
				arr[j]=arr[j-step];
				arr[j-step]=tmp;
				
			}
		}
		step=step/2;
	}
}

int main(){
    int arr[13]={5,2,6,8,3,10,4,7,9,13,12,11,1};
	shellsort(arr,13);
	printarr(arr,13);
}
