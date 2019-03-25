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

int tcp_client(){
	int rc = 0;
	struct socket* sock = NULL;
	struct sockaddr_in addr_srv;
	char buf[1024], *tmp;
	int addr_len;

	sprintf(current->comm, "ksktcli");
	memset(&addr_srv, 0, sizeof(addr_srv));
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(9999);
	addr_srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr_len = sizeof(struct sockaddr_in);

	sock = ksocket(AF_INET, SOCK_STREAM, 0);
    if (sock == NULL)
    {
        printk("cli.socket failed\n");
        return -1;
    }
    if (kconnect(sock, (struct sockaddr*)&addr_srv, addr_len) < 0)
    {
        printk("cli.connect failed\n");
        return -1;
    }
	tmp = inet_ntoa(&addr_srv.sin_addr);
	printk("cli.connected to : %s %d\n", tmp, ntohs(addr_srv.sin_port));
	kfree(tmp);

	rc = krecv(sock, buf, 1024, 0);
	buf[rc] = 0;
	printk("cli.got message : %s", buf);

	kclose(sock);

	return 0;
}
#endif
static int __init client_init(void){
	printk("ksocket tcp client init ok\n");
	kernel_thread(tcp_client, NULL, 0);
	return 0;
}

static void __exit client_exit(void){
	printk("ksocket tcp client exit\n");
}

module_init(client_init);
module_exit(client_exit);
