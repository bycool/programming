#include <stdio.h>

void quicksort(int* arr,int b, int e){
	int bb = b, ee = e;
	int tmp = arr[b],t;
	
	if(b>=e) return;

	while(bb!=ee){
		while(tmp <= arr[ee] && bb<ee){
			ee--;
		}
		while(arr[bb] <= tmp && bb<ee){
			bb++;
		}

		if(bb<ee){
			t = arr[bb];
			arr[bb] = arr[ee];
			arr[ee] = t;
		}
	}
	arr[b] = arr[bb];
	arr[bb] = tmp;

	int i =0;
	for(i=0;i<13;i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
	quicksort(arr,b,bb-1);
	quicksort(arr,ee+1,e);
}

int main(){
	int arr[13]={9,2,6,8,5,10,4,7,3,13,12,11,1};
	quicksort(arr,0,12);

	puts("------------");

	int i =0;
	for(i=0;i<13;i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
}
