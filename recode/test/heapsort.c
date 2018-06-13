#include <stdio.h>


void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

void subtreesort(int* arr, int i, int len){
	int child, tmp;
	for(i=i;2*i+1<len;i=child){
		child = 2*i+1;
		if(arr[child]<arr[child+1] && child+1<len)
			child++;
		if(arr[child]>arr[i]){
			tmp = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int* arr, int len){
	int i = len/2-1;
	int tmp = 0;
	for(i=i;i>=0;i--){
		subtreesort(arr, i, len);
	}

	for(i=len-1;i>=0;i--){
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		subtreesort(arr, 0, i);
	}

}

int main(){
	int arr[10] = {6,1,8,9,0,3,5,6,2,7};
	heapsort(arr,10);
	display(arr,10);
}

