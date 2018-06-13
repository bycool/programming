#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++)
		printf("%d,",arr[i]);
	printf("\b \n");
}

// 1,2,3,4,5,6,7,8,9,0
// i b               e

void quicksort(int* arr, int b, int e){
	int bb = b+1, ee = e;
	int tmp = arr[b],t = 0;

	if(b>=e) return ;

	while(bb!=ee){
		while(arr[ee]>tmp && bb < ee)
			ee--;
		while(arr[bb]<tmp && bb < ee)
			bb++;
		if(bb<ee){
			t = arr[ee];
			arr[ee] = arr[bb];
			arr[bb] = t;
		}
		display(arr,10);
	}
	arr[b] = arr[ee];
	arr[ee] = tmp;
	quicksort(arr,b,ee-1);
	quicksort(arr,ee+1,e);
}

int main(){
	int arr[10] = {6,7,4,1,3,7,9,3,0,8};
	display(arr,10);
	puts("");
	quicksort(arr,0,9);
	puts("");
	display(arr,10);
}


