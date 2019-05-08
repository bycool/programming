#include <stdio.h>

void display(int* arr, int len){
	int i = 0;
	for(i=0; i<len; i++)
		printf("[%d]", arr[i]);
	printf("\n");
}

void quicksort(int* arr, int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b], t;

	if(b>=e) return ;

	while(bb<ee){
		while(arr[ee]>=tmp && bb<ee)
			ee--;
		while(arr[bb]<=tmp && bb<ee)
			bb++;

		if(bb!=ee){
			t = arr[ee];
			arr[ee] = arr[bb];
			arr[bb] = t;
		}
	}

	
	arr[b] = arr[bb];
	arr[bb] = tmp;

	quicksort(arr, b, bb-1);
	quicksort(arr, ee+1, e);
}

void main(){
	int arr[5] = {2,3,1,4,5};
	quicksort(arr, 0,4);
	display(arr, 5);
}
