#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <signal.h>

using namespace std;

class Client
{
    private:
        int sfd;
        struct sockaddr_in serveraddr; 
        int port;
        
    public:
        Client(int port=8888):port(port)
        {
            sfd = socket(AF_INET,SOCK_STREAM,0);
            int ret = 0;
            if(-1 == sfd)
            {
                throw "创建套接字失败";
            }


            serveraddr.sin_family = AF_INET;
            serveraddr.sin_port = htons(port);
            inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr.s_addr);
            ret = connect(sfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
            if(ret == -1)
            {
                throw "连接失败";
            }
        }


        //发送数据
        void sendpost()
        {
            char buf[1024] = {0};
            signal(SIGPIPE,SIG_IGN);
            while(1)
            {
               cout << "请输入你要发送的数据" << endl;
               scanf("%s",buf); 
               //发送数据
               while(send(sfd,buf,strlen(buf),0)<=0)
               {
                    break;
               }
               memset(buf,0,sizeof(buf));
               //接收数据
               while(recv(sfd,buf,sizeof(buf),0) == 0)
               {
                    break;
               }
               cout << buf << endl; 
               memset(buf,0,sizeof(buf));
            }
        }


        ~Client()
        {
            if(-1 == sfd)
            {
                shutdown(sfd,SHUT_RDWR);
            }
        }
};




int main(int argc, char *argv[])
{
    try
    {
        Client *c = new Client;
        c->sendpost();
        delete c;


    }
    catch(const char *str)
    {
        cout << str << endl;
    }


return 0;
}
