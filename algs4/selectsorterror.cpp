#include <iostream>
#include <vector>

using namespace std;

void selectsort(vector<int> vi){
	int i=0,j=1;
	int min=0,tmp=0;
	for(i=0;i<vi.size();i++){
		min = i;
		for(j=i+1;j<vi.size();j++){
			if(vi[min]>vi[j]){
				min=j;
			}
		}

		if(min!=i){
			tmp = vi[i];
			vi[i]=vi[min];
			vi[min]=tmp;
		}
	}

	int len = vi.size();
	cout<<"len:"<<len<<endl;
	i = 0;
	for(i=0;i<len;i++){
		cout<<vi[i]<<endl;
	}
}

void printsort(vector<int> vi){
	int len = vi.size();
	int i = 0;
	for(i=0;i<len;i++){
		cout<<vi[i]<<"\t";
	}
	cout<<endl;
}


int main(){
	vector<int> vi;
	int i = 0;
	while(i!=-1){
		cout<<"input a number:";
		cin>>i;
		vi.push_back(i);
	}
	selectsort(vi);
	printsort(vi);//这里打印的队列是无序的，虽然已经通过选择排序算法排序过，但是可能和vector的下标赋值操作有关，也可能和函数的型参拷贝有关。
}
