#include <iostream>

using namespace std;

void test(){
	const int a = 10;
	int* p =(int*)&a;
	*p = 20;

	int arr[a] = { 0 };

	cout<<a<<endl;
	cout<<*p<<endl;
}

int main(){
	test();
}
