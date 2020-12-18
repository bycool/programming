#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/version.h>
#include <linux/kthread.h>

#include <linux/relay.h>
#include <linux/debugfs.h>


#define NETLINK_M_PORT 17

struct sock *nl_sk = NULL;
u32 user_pid = 0;

static struct rchan *relay_rchan = NULL;
struct dentry *dir = NULL;

int netlink_m_send(char* msg, int len){
	int rc;
	int size;
	struct sk_buff* skb;
	struct nlmsghdr* nlh;

	size = NLMSG_SPACE(len);
	if(user_pid == 0 || nl_sk == NULL || msg == NULL){
		printk("msg = %p, nl_sk = %p, pid_user = %d\n", msg, nl_sk, user_pid);
		return -1;
	}

	skb = alloc_skb(size, GFP_ATOMIC);
	nlh = nlmsg_put(skb, 0, 0, 0, len, 0);
	memcpy(NLMSG_DATA(nlh), msg, len);
	NETLINK_CB(skb).pid = 0;

	rc = netlink_unicast(nl_sk, skb, user_pid, MSG_DONTWAIT);
	if(rc < 0){
		printk("[fds kernel send] net_link: can not unicast skb (%d), retry\n", rc);
		return -1;
	}
	return 0;
}

void netlink_m_recv(struct sk_buff* __skb){
	struct sk_buff* skb;
	struct nlmsghdr *nlh = NULL;

	skb = skb_get(__skb);
	if(skb->len >= sizeof(struct nlmsghdr)){

		nlh = (struct nlmsghdr*)skb->data;

		if((nlh->nlmsg_len >= sizeof(struct nlmsghdr)) && (__skb->len >= nlh->nlmsg_len)){
			user_pid = nlh->nlmsg_pid;
			printk("[netlink_m_recv] data from user : %s\n", (char*)NLMSG_DATA(nlh));
		}
	}
	kfree_skb(skb);
}

int netlink_m_init(void){
	nl_sk = netlink_kernel_create(&init_net, NETLINK_M_PORT, 0, netlink_m_recv, NULL, THIS_MODULE);
	if(!nl_sk){
        printk(KERN_ERR "netlink_m_init::can not create a netlink socket\n");
        return -1;
    }
	printk("netlink_m_init\n");
    return 0;
}

void netlink_m_exit(void){
	netlink_kernel_release(nl_sk);
	printk("netlink_m_exit\n");
}



static int subbuf_start_callback(struct rchan_buf *buf, void *subbuf, void *prev_subbuf, size_t prev_padding)
{
    static int warned;
    if (!relay_buf_full(buf))
        return 1;
    if (!warned) {
        warned = 1;
        printk("relay_buf_full!\n");
    }

    return 0;
}

static void buf_mapped_callback(struct rchan_buf *buf,struct file* pfile){
    printk("buf_mapped_callback\n");
}

static void buf_unmapped_callback(struct rchan_buf* rbuf, struct file* pfile){
    printk("buf_unmapped_callback\n");
}

static struct dentry * create_buf_file_callback(const char *filename, struct dentry *parent, int mode, struct rchan_buf *buf, int *is_global)
{
    *is_global = 1;
    return debugfs_create_file(filename, mode, parent, buf, &relay_file_operations);
}

static int remove_buf_file_callback(struct dentry *dentry)
{
    printk("dentry remove!\n");
    debugfs_remove(dentry);
    return 0;
}

static struct rchan_callbacks relay_callbacks =
{
    .subbuf_start    = subbuf_start_callback,
    .buf_mapped      = buf_mapped_callback,
    .buf_unmapped    = buf_unmapped_callback,
    .create_buf_file = create_buf_file_callback,
    .remove_buf_file = remove_buf_file_callback,
};


int relay_m_init(void){
	relay_rchan = relay_open("nrt", dir, 1024*1024*1024, 1, &relay_callbacks, NULL);
	if(NULL == relay_rchan){
		printk("relay_open() failed.\n");
	}
	printk("relay_m_init\n");
	return 0;
}

void relay_m_exit(void){
	if(relay_rchan) {
		relay_close(relay_rchan);
		relay_rchan = NULL;
	}
	printk("relay_m_exit\n");
}

static int nrt_m_send_netlink(void* data){
	int cnt = 20;
	char buf[16] = "1234567890";
	while(cnt > 0 &&! kthread_should_stop()){
		netlink_m_send(buf, strlen(buf));
		msleep(3000);
		cnt--;
	}
	return 0;
}


static int nrt_m_write_relay(void* data){
	int cnt = 20;
	char buf[16] = "im relay fs";
	
	while(cnt > 0 &&! kthread_should_stop()){
		relay_write(relay_rchan, buf, strlen(buf));
		msleep(3000);
		cnt--;
	}
	return 0;
}

struct task_struct* thd_netlink_send = NULL;
struct task_struct* thd_relay_write = NULL;


int __init nrt_init(void){
	netlink_m_init();
	relay_m_init();

	thd_netlink_send = kthread_create(nrt_m_send_netlink, NULL, "nrt_netlink_send");
	if (!IS_ERR(thd_netlink_send))
		wake_up_process(thd_netlink_send);

	thd_relay_write = kthread_create(nrt_m_write_relay, NULL, "nrt_relay_write");
	if (!IS_ERR(thd_relay_write))
		wake_up_process(thd_relay_write);

	printk("[nrt_init]\n");
	return 0;
}

void __exit nrt_exit(void){

	if(thd_netlink_send->state != TASK_DEAD)
		kthread_stop(thd_netlink_send);

	if(thd_relay_write->state != TASK_DEAD)
		kthread_stop(thd_relay_write);

	relay_m_exit();
	netlink_m_exit();
	printk("[nrt_exit]\n");
}






module_init(nrt_init);
module_exit(nrt_exit);

MODULE_LICENSE("GPL");
