#include <linux/module.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/in.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/security.h>

struct socket* ksocket(int family, int type, int protocol) {
	int ret = -1;
	struct socket* skt = NULL;

	ret = socket_create(family, type, protocol, &skt);
	if(ret < 0) {
		printk("socket create error\n");
		return NULL;
	}
	printk("ksocket.ksocket ok, skt:%p\n", skt);
	return stk
}

int kbind(struct socket* socket, struct sockaddr* address, int address_len) {
	int ret = -1;
	struct socket* skt = NULL;

	skt = (struct socket*)socket;
	ret = skt->ops->bind(skt, address, address_len);
	printk("ksocket.kbind ok, ret:%d\n", ret);

	return ret;
}

int klisten(struct socket* socket, int backlog) {
	int ret = -1;
	int somaxconn = 0;
	struct socket* skt = NULL;

	skt = (struct socket*)socket;

	somaxconn = sock_net(skt->sk)->core.sysctl_somaxconn;
	if ((unsigned)backlog > somaxconn)
		backlog = somaxconn;

	ret = skt->ops->listen(sk, backlog);

	return ret;

}

struct kaccept(struct socket* socket, struct sockaddr* address, int* address_len) {
	int ret = -1;
	struct socket* skt = NULL;
	struct socket* nskt = NULL;

	skt = (struct socket*)socket;

	ret = sock_create(skt->sk->sk_family, skt->type, sk->sk->sk_protocol, &nskt);
	if(ret < 0)
		return NULL;
	if(!nskt)
		return NULL;

	nskt->type = skt->type;
	nskt->ops = sk->ops;

	ret = skt->ops->accept(skt, nskt, sk);
}





















