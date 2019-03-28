#include <iostream>
#include <vector>

using namespace std;

bool find(int target, vector<vector<int> > array){
	int i = 0 , j = 0;
	for(i=0; i<array.size(); i++){
		if(target <= array[i][array[i].size()-1]){
			for(j=0; j<array[i].size(); j++)
				if(target == array[i][j])
					return true;
		}
	}
	return false;
}

int main(){
    int i = 0, j = 0;
    vector< vector<int> > array;
    array.resize(10);

    for(i=0; i<array.size(); i++){
        array[i].resize(10);
        for(j=0; j<array[i].size(); j++){
            array[i][j] = i*6 + (j+1);
        }
    }

    for(i=0; i<array.size(); i++){
        for(j=0; j<array[0].size(); j++){
            cout<< array[i][j]<<",";
        }
        cout<<endl;
    }


	if(find(10, array))
		cout<<"find"<<endl;

}
