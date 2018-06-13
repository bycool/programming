#include <stdio.h>
#include <stdlib.h>

void mergearr(int* src, int* tmp, int b,int c,int e){
	int lb = b,le = c-1;
	int rb = c, re = e;
	int p = b;

	while(lb<=le && rb<=re){
		if(src[lb]<src[rb]){
			tmp[p++] = src[lb++];
		}else{
			tmp[p++] = src[rb++];
		}
	}

	while(lb<=le){
			tmp[p++] = src[lb++];
	}

	while(rb<=re){
			tmp[p++] = src[rb++];
	}
	
	int i = 0;
	for(i=0;i<p;i++){
		src[i] = tmp[i];
	}
}

void msort(int* arr,int* tmp, int b, int e){
	int c;
	if(b<e){
		c = (e+b)/2;
		msort(arr,tmp,b,c);
		msort(arr,tmp,c+1,e);
		mergearr(arr,tmp,b,c+1,e);
	}
}

int main(){
		int arr[11] = {1,3,6,7,9,0,2,4,5,8,10};
	//	int arr[9] = {1,3,63,5,78,9,12,52,8};
		int* tmp = (int*)malloc(sizeof(int)*11);
		msort(arr,tmp,0,10);
		
		int i = 0;
		for(i = 0;i<11;i++){
			printf("%d    ",arr[i]);
		}
		printf("\n");
		free(tmp);
}

