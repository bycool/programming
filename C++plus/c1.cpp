#include <iostream>

using namespace std;

int main(){

	enum week {
		monday,
		tuesday,
		wednesday,
		thursday,
		friday,
		saturday,
		sunday
	} day1;

	day1 = monday;
	enum week day2;
	day2 = tuesday;

	cout<<day1<<endl;
	cout<<day2<<endl;
	cout<<"--------------------"<<endl;

	enum test {
		a,
		b=5,
		c,
		d,
		e,
		f,
		g
	};
	test t1;
	t1 = a;
	enum test t2;
	t2 = d;
	cout<<t1<<endl;
	cout<<t2<<endl;
	cout<<"--------------------"<<endl;

	return 0;
}
