#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main(){
	char str[] = "abcd"; //这样赋值是有'\0'的站位的
	std::cout<<sizeof str<<std::endl;
	std::cout<<strlen(str)<<std::endl;
}
