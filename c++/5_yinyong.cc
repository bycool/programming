#include <iostream>

using namespace std;

int main(void){
	int a = 20;
	int b = 30;
	int *p = &a;
	*p = 40;  //指针修改a

	int &re = a; //re是a的引用
	re = 50;

	cout<<"re:"<< re<<endl;
	cout<<"a :"<< a <<endl;
	
}
