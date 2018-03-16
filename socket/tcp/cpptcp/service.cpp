#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/in.h>
#include <string>

using namespace std;

pthread_mutex_t m_lock = PTHREAD_MUTEX_INITALIZER;

void* pthread_accept(void* arg){
	int conn_fd = 0;

	for(;;){
		pthread_mutex_lock(&m_lock);
		conn_fd = accept((int)arg,(struct sockaddr*)*)
	}
	
}


int main(){
	int service_fd,client_fd;
	char buf[32]={0};
	string buf;
	struct sockaddr_in s_adr,cadr;
	int sin_size;
	int port = 9999;

	cout<<"...Service start..."<<endl;

	service_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == service_fd){
		cout<<"error: socket() fail"<<endl;
		exit(1);
	}
	cout<<"...socket() ok..."<<endl;

	bzero(&s_adr, sizeof(struct sockaddr_in));
	s_adr.sin_family=AF_INET;
	s_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	s_adr.sin_port=htons(port);
	if(-1==bind(service_fd,(struct sockaddr*)(&s_adr),sizeof(struct sockaddr))){
		cout<<"error: bind() fail"<<endl;
		exit(1);
	}
	cout<<"...bind() ok..."<<endl;

	if(-1==listen(service_fd,64)){
		cout<<"error: listen() fail"<<endl;
		exit(1);
	}
	cout<<"...listen() ok..."<<endl;



	

}

