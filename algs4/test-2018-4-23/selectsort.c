#include <stdio.h>

//6,3,1,5,2,4,9,7,0,8

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\n");
}

int selectsort(int* arr, int len){
	int i, j, min, tmp;
	for(i=0;i<len;i++){
		min=i;
		tmp=arr[i];
		for(j=i;j<len;j++){
			if(arr[min]>arr[j]){
				min = j;
			}
		}
		if(min!=i){
			arr[i]=arr[min];
			arr[min]=tmp;
		}
	}
	return 0;
}

int main(){
	int arr[10] = {6,3,1,5,2,4,9,7,0,8};
	selectsort(arr,10);
	display(arr,10);
}

