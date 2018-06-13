#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	vector<int> vi;
	vi.push_back(1);
	vi.push_back(4);
	vi.push_back(2);
	vi.push_back(6);
	vi.push_back(5);
	vi.push_back(7);
	vi.push_back(3);
	vector<int>::iterator iter = vi.begin();
	while(iter!=vi.end()){
		cout<<*iter<<',';
		iter++;
	}
	cout<<"\b "<<endl;
	sort(vi.begin(),vi.end());
	iter = vi.begin();
	while(iter!=vi.end()){
		cout<<*iter<<',';
		iter++;
	}
	cout<<"\b "<<endl;
}
