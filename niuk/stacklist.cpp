#include <iostream>
#include <stack>

using namespace std;

class array {
public:
	void push(int a){
		while(!st2.empty()){
			st1.push(st2.top());
			st2.pop();
		}
		st1.push(a);
		while(!st1.empty()){
			st2.push(st1.top());
			st1.pop();
		}
	};
	int pop(){
		int rc = st2.top();
		st2.pop();
		return rc;
	};
private:
	stack<int> st1;
	stack<int> st2;
};

int main(){
	array ar1;
	ar1.push(1);
}
