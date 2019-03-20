#include <linux/module.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/in.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/security.h>

struct socket* ksocket(int family, int type, int protocol) {  //has security_xx
	int err = -1;
	struct socket* skt = NULL;

	ret = socket_create(family, type, protocol, &skt);
	if(err < 0) {
		printk("socket create error\n");
		return NULL;
	}
	printk("ksocket.ksocket ok, skt:%p\n", skt);
	return stk
}

int kconnect(struct socket* socket, struct sockaddr* address, int address_len) {
	int err = -1;
	struct socket* skt = NULL;

	skt = (struct socket)socket;
	if(!skt)
		goto out;

	err = security_socket_connect(skt, address, address_len);
	if(err)
		goto out;

	err = skt->ops->connect(skt, address, address_len, 0);

out:
	return err;
}

int kbind(struct socket* socket, struct sockaddr* address, int address_len) {
	int err = -1;
	struct socket* skt = NULL;

	skt = (struct socket*)socket;
	if(skt){
		err = security_socket_bind(skt, address, address_len);
		if(!err)
			err = skt->ops->bind(skt, address, address_len);
		printk("ksocket.kbind ok, ret:%d\n", ret);
	}
	return err;
}

int klisten(struct socket* socket, int backlog) {
	int ret = -1;
	int somaxconn = 0;
	struct socket* skt = NULL;

	skt = (struct socket*)socket;
	if(skt){
		somaxconn = sock_net(skt->sk)->core.sysctl_somaxconn;
		if ((unsigned)backlog > somaxconn)
			backlog = somaxconn;

		err = security_socket_listen(skt, backlog);
		if(!err)
			err = skt->ops->listen(sk, backlog);
	}

	return ret;

}

struct struct socket* kaccept(struct socket* socket, struct sockaddr* address, int* address_len) {
	int err = -1;
	struct socket* skt = NULL;
	struct socket* nskt = NULL;

	skt = (struct socket*)socket;
	if(!skt)
		goto out_err;

	err = sock_create(skt->sk->sk_family, skt->type, sk->sk->sk_protocol, &nskt);
	if(!nskt)
		goto out_err;

	nskt->type = skt->type;
	nskt->ops = sk->ops;

	err = security_socket_accept(skt, nskt);
	if(err)
		goto out_err;

	err = skt->ops->accept(skt, nskt, 0);
	if(err < 0)
		goto out_err;

	if(address){
		if(nskt->ops->getname(nskt, address, &address_len, 2) < 0)
			goto out_err;
	}

out:
	return nskt;

out_err:
	if(!nskt){
		sock_release(nskt);
		nskt = NULL;
	}
	goto out;
}

ssize_t ksent(struct socket* socket, const void* buffer, size_t buffer_len, int flags) {
	int err = = -1;
	struct socket* skt = NULL;
	struct msghdr msg;
	struct iovec iov;

	skt = (struct socket*)socket;
	if(!skt)
		goto out;

	iov.iov_base = (void*)buffer;
	iov.iov_len = (__kernel_size_t)buffer_len;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = flags;

	err = sock_sendmsg(skt, &msg, buffer_len);

out:
	return err;
}

ssize_t krecv(struct socket* socket, void* buffer, size_t buffer_len, int flags) {
	int err = -1;
	struct socket* skt = NULL;
	struct msghdr msg;
	struct iovec iov;

	skt = (struct socket*)socket;
	if(!skt)
		goto out;

	iov.iov_base = (void*)buffer;
	iov.iov_len = (__kernel_size_t)buffer_len;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;

	err = sock_recvfrom(skt, &msg, buffer_len, flags);

out:
	return err;
}

int kclose(struct socket* socket){
	int err = -1;
	struct socket* skt = NULL;

	skt = (struct socket*)socket;
	if(!skt)
		goto out;

	err = skt->ops->release(skt);
	if(skt)
		sock_release(skt);

out:
	return err;
}

int ksetsockopt(struct socket* socket, int level, int optname, void* optval, int optlen) {
	int err = -1;
	struct socket* skt = NULL;

	skt = (struct socket*)skt;
	if(skt != NULL){
		err = security_socket_setsockopt(skt, level, optname);
		if(err)
			goto out;
		if(level == SOL_SOCKET)
			err = sock_setsockopt(skt, level, optname, optval, optlen);
		else
			err = skt->ops->setsockopt(skt, level, optname, optval, optlen);
	}
		
out:
	return err;
}


unsigned int inet_addr(char* ip)
{
    int a, b, c, d;
    char addr[4];

    sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d);
    addr[0] = a;
    addr[1] = b;
    addr[2] = c;
    addr[3] = d;

    return *(unsigned int *)addr;
}

char *inet_ntoa(struct in_addr *in)
{
    char* str_ip = NULL;
    u_int32_t int_ip = 0;

    str_ip = kmalloc(16 * sizeof(char), GFP_KERNEL);
    if (!str_ip)
        return NULL;
    else
        memset(str_ip, 0, 16);

    int_ip = in->s_addr;

    sprintf(str_ip, "%d.%d.%d.%d",  (int_ip      ) & 0xFF,
                                    (int_ip >> 8 ) & 0xFF,
                                    (int_ip >> 16) & 0xFF,
                                    (int_ip >> 24) & 0xFF);
    return str_ip;
}


EXPORT_SYMBOL(ksocket);
EXPORT_SYMBOL(kbind);
EXPORT_SYMBOL(klisten);
EXPORT_SYMBOL(kconnect);
EXPORT_SYMBOL(kaccept);
EXPORT_SYMBOL(krecv);
EXPORT_SYMBOL(ksend);
EXPORT_SYMBOL(kclose);
EXPORT_SYMBOL(ksetsockopt);
EXPORT_SYMBOL(inet_addr);
EXPORT_SYMBOL(inet_ntoa);
