#include <stdio.h>

void selectsort(int* arr,int len){
	int i=0,j=0;
	int tmp=0,min=0;

	for(i=0;i<len;i++){
		min = i;
		for(j=i+1;j<len;j++){
			if(arr[min]>arr[j])
				min=j;
		}
		if(min!=i){
			tmp=arr[i];
			arr[i]=arr[min];
			arr[min]=tmp;
		}
	}
}

void printsort(int* arr,int len){
	int i = 0;
	for(i=0;i<len;i++){
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

int main(){
	int len = 0;
	printf("input len of arr:");
	scanf("%d",&len);
	int arr[len];
	int i = 0;
	for(i=0;i<len;i++){
		printf("input a number:");
		scanf("%d",&arr[i]);
	}

	printsort(arr,len);
	selectsort(arr,len);
	printsort(arr,len);
	
}

