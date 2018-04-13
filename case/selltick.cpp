#include <iostream>
#include <mutex>
#include <unistd.h>
#include <thread>

using namespace std;

mutex mlock;

int tick = 20;

void* seller(void* no){
	mlock.lock();
	while(1){
		if(tick>0){
			tick--;
			cout<<"no."<<(int*)no<<" sell a tick, the rest tick is "<<tick<<endl;
			mlock.unlock();
			sleep(1);
		}else{
			mlock.unlock();
			break;
		}
	}
}

int main(){
	thread t1(seller,(void*)1), t2(seller,(void*)2);
	t1.detach();
	t2.detach();

	getchar();
}
