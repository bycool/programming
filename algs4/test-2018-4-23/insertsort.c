#include <stdio.h>

// 6,3,1,5,2,4,9,7,0,8

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\n");
}

int insertsort(int* arr, int len){
	int i, j, tmp;
	for(i=1;i<len;i++){
		tmp = arr[i];
		j=i;
		while(j>0 && tmp < arr[j-1]){
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = tmp;
	}
	return 0;	
}

int main(){
	int arr[10] = {6,3,1,5,2,4,9,7,0,8};
	insertsort(arr,10);
	display(arr,10);
	
}
