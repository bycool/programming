#include <stdio.h>


void test() {
	int a = 1;
	int b = 2;

	const int* c = &a;  //C指向的内存内的内容不可修改,指针指向的地址是可以改变的。
	printf("c:%d\n", *c);
	c = &b;
	printf("c:%d\n", *c);
//	*c = 3; //error

	int* const d = &a; //指针指向的内存内的内容是可修改的，但是指针指向是不可以改变的
	printf("d:%d\n", *d);
	*d = 3;
	printf("d:%d\n", *d);
//	d = &b; //error

}

void test1(){
	const int a = 10;
//	int arr[a] = { 0 }; error

	int* p = &a;
	*p = 70;
	printf("a: %d\n", a);

}

void main(){
	//test();
	test1();
}
