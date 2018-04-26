#include <stdio.h>

// 6,2,11,12,5,3,4,14,9,7,1,10,8,13,0

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf(",%d",arr[i]);
	printf("\n");
}

void quicksort(int* arr, int b , int e){
	int bb = b, ee = e;
	int tmp = arr[b], t;

	if(b>=e) return ;

	while(bb!=ee){
		while(bb<ee && tmp <= arr[ee])
			ee--;
		while(bb<ee && tmp >= arr[bb])
			bb++;
		if(ee!= bb){
			t = arr[ee];
			arr[ee] = arr[bb];
			arr[bb] = t;
		}
	}
	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr,b,bb-1);
	quicksort(arr,bb+1,e);
}

int main(){
	int arr[15] = {6,2,11,12,5,3,4,14,9,7,12,10,8,13,0};
	quicksort(arr,0,14);
	display(arr,15);
}


