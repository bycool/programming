#include <stdio.h>
void printarr(int* arr,int len){
	int i =0;
	for(i=0;i<len;i++){
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

void shellsort(int* arr, int len){
	int h = 1,i=0,j=0,tmp=0;
	while(h<len/3) {h=3*h+1;}
	while(h>=1){
		printf("h:%d\n",h);
		for(i = h;i<len;i++){

			for(j=i;j>=h&&(arr[j]<arr[j-h]);j-=h){
				tmp=arr[j];
				arr[j]=arr[j-h];
				arr[j-h]=tmp;
				printarr(arr,len);
			}
		}
		h=h/3;
	}
}


int main(){
	int arr[13]={5,2,6,8,3,10,4,7,9,13,12,11,1};
	printarr(arr,13);
	printf("\n");
	shellsort(arr,13);
}
