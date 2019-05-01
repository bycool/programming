#include <stdio.h>


/*
 * 二分查找是基于连续有序的存储空间，
 * 通过范围的中间位置的值和被查找值的比较，
 * 来缩小范围，直到找到。
 */

int binarysearch(int* arr, int len, int key){
	int i = 0;
	while(i<=len){
		int mid = i+(len-i)/2;
		if(key<arr[mid]){
			len = mid-1;
		}else if(key>arr[mid]){
			i = mid+1;
		}else if(key == arr[mid]){
			return mid;
		}
	}
	return 0;
}

int main(){
	int arr[10]={1,4,6,8,10,14,15,17,19,20};
	int index = binarysearch(arr,10,6);
	printf("%d\n",index);
}
