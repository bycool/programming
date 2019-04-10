#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int binarysearch(int key, vector<int> vi){
	sort(vi.begin(),vi.end());
	int i = 0;
	int len = vi.size();
	while(i<=len){
		int mid = i+(len-i)/2;
		if(key<vi[mid]){
			len = mid - 1 ;
		}else if(key>vi[mid]){
			i = mid + 1;
		}else{
			return mid;
		}
	}
}

int main(){
	vector<int> vi;
	vi.push_back(3);
	vi.push_back(4);
	vi.push_back(5);
	vi.push_back(1);
	vi.push_back(9);
	vi.push_back(2);
	vi.push_back(6);
	vi.push_back(7);
	vi.push_back(8);
	vi.push_back(10);
	vi.push_back(12);
	vi.push_back(13);
	vi.push_back(15);
	vi.push_back(19);
	vi.push_back(21);
	
	int i = binarysearch(6,vi);

	cout<<i<<endl;

}
