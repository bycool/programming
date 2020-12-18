/* *
 * system : rhel6.9 
 * kernel version : 2.6.32-696.el6.x86_64
 * */

#include <linux/netlink.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/version.h>

#define NETLINK_TEST_PORT 29

struct sock *nl_sk = NULL;
u32 user_pid = 0;

void netlink_m_recv(struct sk_buff* __skb){
	struct sk_buff* skb;
	struct nlmsghdr *nlh = NULL;

	skb = skb_get(__skb);
	if(skb->len >= sizeof(struct nlmsghdr)){
		nlh = (struct nlmsghdr*)skb->data;
		if((nlh->nlmsg_len >= sizeof(struct nlmsghdr)) && (__skb->len >= nlh->nlmsg_len)){
			
		}
	}
}



static int __init kernel_nl_init(void){
	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST_PORT, 0, netlink_m_recv, NULL, THIS_MODULE);
	if(!nl_sk){
		printk("kernel_nl_init: can't create a netlink socket\n");
		return -1;
	}
	printk("[kernel_nl_init]\n");
	return 0;
}

static void __exit kernel_nl_exit(void){
	if(nl_sk){
		netlink_kernel_release(nl_sk);
		nl_sk = NULL;
	}
}

