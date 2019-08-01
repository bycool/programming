#include <iostream>

using namespace std;

int main(){
	int a = 1, b = 2;
	int rc = -1;

	rc = a>b?a:b;
	cout<<"rc:"<<rc<<endl;

	(a>b?a:b) = 10;
	cout<<"a:"<<a<<" b:"<<b<<endl;
}
