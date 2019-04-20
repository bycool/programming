#include <stdio.h>
#include <stdlib.h>

void mergesub(int* arr, int* tmp, int b, int c, int e){
	int lb = b, le = c-1;
	int rb = c, re = e;
	int p = b;

	while(lb<=le && rb<=re){
		if(arr[lb] < arr[rb])
			tmp[p++] = arr[lb++];
		else
			tmp[p++] = arr[rb++];
	}
	while(lb<=le)
		tmp[p++] = arr[lb++];

	while(rb<=re)
		tmp[p++] = arr[rb++];

	int i = 0;
	for(i=0; i<p; i++)
		arr[i] = tmp[i];
}

void mergesort(int* arr, int* tmp, int b, int e){
	int c = 0;
	if(b<e){
		c = (b+e)/2;
		mergesort(arr, tmp, b, c);
		mergesort(arr, tmp, c+1, e);
		mergesub(arr, tmp, b, c+1, e);
	}
}

int main(){
    int arr[13]={9,2,6,8,5,10,4,7,3,13,12,11,1};
	int* tmp = (int*)malloc(13*sizeof(int));
    mergesort(arr, tmp, 0, 12);
	free(tmp);

    int i =0;
    for(i=0;i<13;i++){
        printf("%d,",arr[i]);
    }
    printf("\n");
}

