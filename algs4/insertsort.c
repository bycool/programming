#include <stdio.h>

void insertsort(int* arr,int len){
	int i = 0,j = 0,k=0;
	int tmp = 0;
	for(i=1;i<len;i++){
		tmp = arr[i];
		j = i-1;
		while(j>=0&&tmp<arr[j]){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=tmp;
	
		for(k=0;k<8;k++)
			printf("%d\t",arr[k]);
		printf("\n--------\n");
	}
}

int main(){
	int i = 0;
	int arr[8]={6,1,3,5,2,4,8,7};
	insertsort(arr,8);
	for(i=0;i<8;i++)
		printf("%d\t",arr[i]);
	printf("\n");
	return 0;
}
