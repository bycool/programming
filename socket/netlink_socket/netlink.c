#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_FDS_PORT 22

struct sock *nl_sk = NULL;
u32 pid_user = 0;

int ten_netlink_send(char* msg, int len){
	int rc = 0;
	int size;
	struct sk_buff *skb;
    struct nlmsghdr *nlh;

	size = NLMSG_SPACE(len);

	if(pid_user == 0 || nl_sk == NULL || msg == NULL)
	{
		printk("msg = %p, nl_sk = %p, pid_user = %d\n", msg, nl_sk, pid_user);
		return -1;
	}

	skb = alloc_skb(size, GFP_ATOMIC);

	nlh = nlmsg_put(skb, 0, 0, 0, len, 0);
	memcpy(NLMSG_DATA(nlh), msg, len);
	NETLINK_CB(skb).pid = 0;
	
	rc = netlink_unicast(nl_sk, skb, pid_user, MSG_DONTWAIT);
    if(rc < 0)
    {
        printk("[ten kernel send] net_link: can not unicast skb (%d), retry\n", rc);
		return -1;
    }
	printk( "[ten kernel send] netlink_unicast return: %d\n", rc);
	return 0;
}

void ten_netlink_recv(struct sk_buff *__skb)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh = NULL;
	char cmd;

	printk( "[ten kernel recv] begin ten_netlink_recv\n");
	skb = skb_get(__skb);

	if(skb->len >= sizeof(struct nlmsghdr))
	{
		nlh = (struct nlmsghdr *)skb->data;
        if((nlh->nlmsg_len >= sizeof(struct nlmsghdr)) && (__skb->len >= nlh->nlmsg_len))
		{
            pid_user = nlh->nlmsg_pid;
			printk( "[ten kernel recv] len: %d user.data: %s\n", nlh->nlmsg_len, (char *)NLMSG_DATA(nlh));
			memcpy(&cmd, NLMSG_DATA(nlh), 1);
			if( cmd == 'q' )
			{
				printk("user app quit\n");
				ten_netlink_send(&cmd, 1);
			}
		}
	}
	kfree_skb(skb);
}

int ten_netlink_init(void){
	nl_sk = netlink_kernel_create(&init_net, NETLINK_FDS_PORT, 0, ten_netlink_recv, NULL, THIS_MODULE);
	if(nl_sk == NULL)
	{
		printk("[ten kernel init] net_link: FDS Cannot create netlink socket\n");
		return -1;
	}
	printk("[ten kernel init] ten net_link: create socket OK.\n");
	return 0;
}

void ten_netlink_exit(void)
{
	if(nl_sk != NULL)
    {
        sock_release(nl_sk->sk_socket);
    }
    printk("netlink module exit.\n");
}

