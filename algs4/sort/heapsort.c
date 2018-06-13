#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

void subtreesort(int* arr, int i, int len){
	int child, tmp;
	for(;2*i+1<len;i=child){
		child = 2*i+1;
		if(arr[child]<arr[child+1] && child+1<len)
			child++;

		if(arr[i]<arr[child]){
			tmp = arr[i];
			arr[i] = arr[child];
			arr[child] = tmp;
		}else{
			break;
		}
	}
}

void heapsort(int* arr, int len){
	int i, tmp;
	for(i=len/2-1;i>=0;i--)
		subtreesort(arr,i,len);

	for(i=len-1;i>0;i--){
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		subtreesort(arr,0,i);
	}
}

int main(){
	int arr[10] = {9,2,6,1,7,3,5,3,1,0};
	heapsort(arr,10);
	display(arr,10);
}

