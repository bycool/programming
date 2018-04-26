#include <stdio.h>
#include <stdlib.h>

void mergearr(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;
	int rb = c, re = e;
	int p = b;
	while(lb<=le && rb<=re){
		if(arr[lb]<arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}
	while(lb<=le){
		tmp[p++] = arr[lb++];
	}
	while(rb<=re){
		tmp[p++] = arr[rb++];
	}
	int i = 0;
	for(i = 0;i<=e;i++){
		arr[i] = tmp[i];
	}
}

void msort(int* arr, int* tmp, int b ,int e){
	int c;
	if(b<e){
		c = (b+e)/2;
		msort(arr,tmp,b,c);
		msort(arr,tmp,c+1,e);
		mergearr(arr,tmp,b,c+1,e);
	}
}

void display(int* arr, int len){
	int i = 0;
	for(i=0;i<len;i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
}

int main(){
	int arr[10] = {6,7,4,2,1,8,3,5,9,0};
	int* tmp = (int*)malloc(10);
	msort(arr,tmp,0,9);
	display(arr,10);

}
