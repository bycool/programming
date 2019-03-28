#include <iostream>
#include <vector>

using namespace std;

int main(){
	int i = 0, j = 0;
	vector< vector<int> > array;
	array.resize(6);

	for(i=0; i<6; i++){
		array[i].resize(6);
		for(j=0; j<6; j++){
			array[i][j] = i*6 + (j+1);
		}
	}

	for(i=0; i<array.size(); i++){
		for(j=0; j<array[0].size(); j++){
			cout<< array[i][j]<<",";
		}
		cout<<endl;
	}

}
