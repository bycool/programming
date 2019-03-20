#include <iostream>
#include <string>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>


using namespace std;


class Server
{
private:
    int port; //端口号
    int sfd;  //监听套接字
    int cfd;  //客户端套接字
    struct sockaddr_in server_addr; //服务端ip
    struct sockaddr_in client_addr; //客户端ip
    socklen_t c_len;
public:
    //有参构造函数
    Server(int port=8888):port(port),sfd(-1),cfd(-1)
    {
        sfd = socket(AF_INET,SOCK_STREAM,0);
        if(-1 == sfd)
        {
            throw("创建套接字失败\n");            
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
        listen(sfd,128);
    }
    //函数运行
    void run()
    {
        if(sfd >= 0)
        {
            cfd = accept(sfd,(struct sockaddr*)&client_addr,&c_len);
            char buf[BUFSIZ] = {0};
            int len = 0;
            int opt = 1;
            setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            while(1)
            {
               len = recv(cfd,buf,sizeof(buf),0);
               if(len <= 0)
               {     
                    break;
               }
               cout <<"\n读到数据了\n" <<endl;
               cout << buf <<endl;
               send(cfd,buf,strlen(buf),0);
               memset(buf,0,sizeof(buf));
            }
        } 
    }


    ~Server()
    { 
       cout <<"析构" <<endl;;//析构
       if(-1 != sfd)
       shutdown(sfd,SHUT_RDWR);
       if(-1 != cfd)
       shutdown(cfd,SHUT_RDWR);
    }


};


void test()
{
    Server *s = NULL;
    try
    {
      s = new Server;    
      s->run();
    }
    catch(char const*str)
    {
        cout << str <<endl;
    }
    catch(...)
    {
        cout<<"万能捕获"<<endl;
    }
    delete s;
}


int main(int argc, char *argv[])
{
    test();
    return 0;
}
