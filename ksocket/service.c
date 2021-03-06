#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/in.h>

#if 1
#include "ksocket.h"

static int port = 9999;

int tcp_service(void *arg){
	struct socket* sockfd_srv;
	struct socket* sockfd_cli;
    struct sockaddr_in addr_srv;
    struct sockaddr_in addr_cli;
    char buf[1024], *tmp;
    int addr_len, len;

	sprintf(current->comm, "ksktsrv");
	sockfd_srv = sockfd_cli = NULL;
    memset(&addr_cli, 0, sizeof(addr_cli));
    memset(&addr_srv, 0, sizeof(addr_srv));
    addr_srv.sin_family = AF_INET;
    addr_srv.sin_port = htons(port);
    addr_srv.sin_addr.s_addr = INADDR_ANY;
    addr_len = sizeof(struct sockaddr_in);

    sockfd_srv = ksocket(AF_INET, SOCK_STREAM, 0);
    printk("srv.sockfd_srv = 0x%p\n", sockfd_srv);
    if (sockfd_srv == NULL)
    {
        printk("srv.socket failed\n");
        return -1;
    }
    if (kbind(sockfd_srv, (struct sockaddr *)&addr_srv, addr_len) < 0)
    {
        printk("srv.bind failed\n");
        return -1;
    }

    if (klisten(sockfd_srv, 10) < 0)
    {
        printk("srv.listen failed\n");
        return -1;
    }

    sockfd_cli = kaccept(sockfd_srv, (struct sockaddr *)&addr_cli, &addr_len);
    if (sockfd_cli == NULL)
    {
        printk("srv.accept failed\n");
        return -1;
    }
    else
        printk("srv.sockfd_cli = 0x%p\n", sockfd_cli);

    tmp = inet_ntoa(&addr_cli.sin_addr);
    printk("srv.got connected from : %s %d\n", tmp, ntohs(addr_cli.sin_port));
    kfree(tmp);

    len = sprintf(buf, "%s", "Hello, welcome to ksocket tcp srv service\n");
    ksend(sockfd_cli, buf, len, 0);
	printk("srv.send buf to client\n");

    kclose(sockfd_cli);
    kclose(sockfd_srv);

    return 0;

}

#endif
static int __init ksocket_tcp_srv_init(void)
{
    printk("srv.ksocket tcp srv init ok\n");
    kernel_thread(tcp_service, NULL, 0);
    return 0;
}

static void __exit ksocket_tcp_srv_exit(void)
{
    printk("srv.ksocket tcp srv exit\n");
}

module_init(ksocket_tcp_srv_init);
module_exit(ksocket_tcp_srv_exit);

