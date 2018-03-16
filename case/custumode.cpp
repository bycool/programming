#include <stack>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
using namespace std;

static stack<int> si;

mutex m_lock;

void* pushstack(){
	while(1){
		m_lock.lock();
		if(si.size()<10){
			si.push(1);
			cout<<"push stack"<<endl;
			m_lock.unlock();
		}else{
			cout<<"stack is full"<<endl;
			m_lock.unlock();
		}
	}
}

void* popstack(){
	while(1){
		m_lock.lock();
		if(si.size()>0){
			si.pop();
			cout<<"pop stack"<<endl;
			m_lock.unlock();
		}else{
			cout<<"stack is empty"<<endl;
			m_lock.unlock();
		}
	}
}

int main(){
	thread t1(pushstack);
	thread t2(popstack);
	t1.detach();
	t2.detach();
	int i;
	cin>>i;
}

