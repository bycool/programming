#include <stdio.h>
void printarr(int* arr,int len){
	int i =0;
	for(i=0;i<len;i++){
		printf("%d\t",arr[i]);
	}
	printf("\n");
}

/*
 *	希尔排序是对范围分段，段1，段2，段3 等等
 *	段1[0]和段2[0]进行比较，进行比较,超过段2，进入段3时，就会出现3个数进行比较的过程。
 *	所以段1是基准，超过段1最大，小于数组最大的范围是需要遍历的。
 *
 *	如代码里的arr[j]类似与基准比较值，每次都先取它，和低段位相同位置的值比较，当arr[j]处于段1时，不同段的统一位置的值就比较完成。
 *	h很好的起了界限划定的功能，它是每段的长度，也是段1的之后的第一个元素的标识。h=4  arr[4]是段2的第一个元素。
 */

void shellsort(int* arr, int len){
	int h = 1,i=0,j=0,tmp=0;
	while(h<len/3) {h=3*h+1;}
	while(h>=1){
		printf("h:%d\n",h);
		for(i = h;i<len;i++){

			for(j=i;j>=h&&(arr[j]<arr[j-h]);j-=h){
//				printf("arr[%d]:%d  arr[%d]:%d\n",j,arr[j],j-h,arr[j-h]);
				tmp=arr[j];
				arr[j]=arr[j-h];
				arr[j-h]=tmp;
			}

			printarr(arr,len);
		}
		h=h/3;
	}
}


int main(){
	int arr[13]={9,2,6,8,5,10,4,7,3,13,12,11,1};
	printarr(arr,13);
	printf("\n");
	shellsort(arr,13);
}
