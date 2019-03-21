#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/in.h>

#include "ksocket.h"

static int port = 9999;

int tcp_service(void *arg){
	struct socket* sockfd_srv, sockfd_cli;
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
    printk("sockfd_srv = 0x%p\n", sockfd_srv);
    if (sockfd_srv == NULL)
    {
        printk("socket failed\n");
        return -1;
    }
    if (kbind(sockfd_srv, (struct sockaddr *)&addr_srv, addr_len) < 0)
    {
        printk("bind failed\n");
        return -1;
    }

    if (klisten(sockfd_srv, 10) < 0)
    {
        printk("listen failed\n");
        return -1;
    }

    sockfd_cli = kaccept(sockfd_srv, (struct sockaddr *)&addr_cli, &addr_len);
    if (sockfd_cli == NULL)
    {
        printk("accept failed\n");
        return -1;
    }
    else
        printk("sockfd_cli = 0x%p\n", sockfd_cli);

    tmp = inet_ntoa(&addr_cli.sin_addr);
    printk("got connected from : %s %d\n", tmp, ntohs(addr_cli.sin_port));
    kfree(tmp);

    len = sprintf(buf, "%s", "Hello, welcome to ksocket tcp srv service\n");
    ksend(sockfd_cli, buf, len, 0);

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        len = krecv(sockfd_cli, buf, sizeof(buf), 0);
        if (len > 0)
        {
            printk("got message : %s\n", buf);
            ksend(sockfd_cli, buf, len, 0);
            if (memcmp(buf, "quit", 4) == 0)
                break;
        }
    }

    kclose(sockfd_cli);
    kclose(sockfd_srv);

    return 0;

}

static int ksocket_tcp_srv_init(void)
{
    kernel_thread(tcp_service, NULL, 0);

    printk("ksocket tcp srv init ok\n");
    return 0;
}

static void ksocket_tcp_srv_exit(void)
{
    printk("ksocket tcp srv exit\n");
}

module_init(ksocket_tcp_srv_init);
module_exit(ksocket_tcp_srv_exit);

