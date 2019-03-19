#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/rtnetlink.h>

#define buflen 8196
#define linebuf 256

typedef struct netinfo {
	char card_name[32];
	char ip_addr[32];
	char net_mask[18];
	char gate_way[18];
	char dns_addr[18];
	char machine[32];
}netinfo;

int get_local_gateway_by_name(char* card_name, netinfo* ni){
	struct nlmsghdr *nlmsg;
	struct rtattr *rtattr;
	struct rtmsg *rtmsg;
	struct nlmsghdr *nlhdr;
	int rtlen;
	unsigned int gateway;
	unsigned int dstaddr;
	unsigned int srcaddr;
	char ifname[IF_NAMESIZE];
	int readlen = 0;
	int msglen = 0;
	char *tempbuf = NULL;
	struct in_addr gate;
	struct in_addr dst;
	char msgbuf[buflen];
	char* pmsgbuf = msgbuf;
	int fd = -1;
	int len;
	int msgseq = 0;

	if((fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0) {
		printf("Socket Creat error\n");
		return -1;
	}

	memset(msgbuf, 0x0, buflen);

	nlmsg = (struct nlmsghdr *)pmsgbuf;
	rtmsg = (struct rtmsg *)NLMSG_DATA(nlmsg);

	nlmsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
	nlmsg->nlmsg_type = RTM_GETROUTE;
	nlmsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST;
	nlmsg->nlmsg_seq = msgseq++;
	nlmsg->nlmsg_pid = getpid();

	if(send(fd, nlmsg, nlmsg->nlmsg_len, 0) < 0) {
		printf("write to socket error\n");
		return -1;
	}

	do{
		if((readlen = recv(fd, pmsgbuf, buflen-msglen, 0)) < 0){
			printf("sock read error\n");
			return -1;
		}

		nlhdr = (struct nlmsghdr*)pmsgbuf;
		if((NLMSG_OK(nlhdr, readlen) == 0) || (nlhdr->nlmsg_type == NLMSG_ERROR)) {
			printf("recvieved packet error\n");
			return -1;
		}
		if(nlhdr->nlmsg_type == NLMSG_DONE) {
			break;
		}else {
			pmsgbuf += readlen;
			msglen += readlen;
		}

		if((nlhdr->nlmsg_flags & NLM_F_MULTI) == 0) {
			break;
		}
	}while(nlhdr->nlmsg_seq != msgseq || nlhdr->nlmsg_pid != getpid());

	if(msglen < 0){
		printf("read from socket error\n");
		return -1;
	}

	for(;NLMSG_OK(nlmsg, msglen); nlmsg = NLMSG_NEXT(nlmsg, msglen))
	{
		memset(&gateway, 0x0, sizeof(gateway));
		memset(&dstaddr, 0x0, sizeof(dstaddr));
		rtmsg = (struct rtmsg*)NLMSG_DATA(nlmsg);

		if((rtmsg->rtm_family != AF_INET) || (rtmsg->rtm_table != RT_TABLE_MAIN))
			return -1;

		rtattr = (struct rtattr*)RTM_RTA(rtmsg);
		rtlen = RTM_PAYLOAD(nlmsg);
		for( ;RTA_OK(rtattr, rtlen); rtattr = RTA_NEXT(rtattr, rtlen))
		{
			switch(rtattr->rta_type) {
				case RTA_OIF:
					if_indextoname(*(int *)RTA_DATA(rtattr), ifname);
					break;
				case RTA_GATEWAY:
					gateway = *(unsigned int*)RTA_DATA(rtattr);
					break;
				case RTA_PREFSRC:
					srcaddr = *(unsigned int*)RTA_DATA(rtattr);
					break;
				case RTA_DST:
					dstaddr = *(unsigned int*)RTA_DATA(rtattr);
					break;
			}
		}
		dst.s_addr = dstaddr;
		if(strstr((char*)inet_ntoa(dst), "0.0.0.0")) {
			if(!strcmp(ifname, card_name)) {
				gate.s_addr = gateway;
				sprintf(ni->gate_way, (char*)inet_ntoa(gate));
			}
		}

	}
	return 0;
}

int get_local_netinfo_by_name(char* card_name, netinfo* ni){
	int fd = -1;
	int ret = -1;
	struct sockaddr_in sin;
	struct ifreq req;

	memset(&req, 0x0, sizeof(req));

	ret = fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(ret > 0)
	{
		memcpy(req.ifr_name, card_name, strlen(card_name));
		ret = ioctl(fd, SIOCGIFADDR, &req);
		if(!ret)
		{
			memcpy(&sin, &req.ifr_addr, sizeof(sin));
			ret = snprintf(ni->ip_addr, sizeof(ni->ip_addr), "%s", inet_ntoa(sin.sin_addr));
		}
		ret = ioctl(fd, SIOCGIFNETMASK, &req);
		if(!ret)
		{
			memcpy(&sin, &req.ifr_netmask, sizeof(sin));
			ret = snprintf(ni->net_mask, sizeof(ni->net_mask), "%s", inet_ntoa(sin.sin_addr));
		}
		close(fd);
	}

	return ret;
}

int get_local_netcard_names(char* cards_name, int buf_size){
	int cnt = 0;
	int i = 0;
	int fd = -1;
	int ret = -1;
	struct ifconf ifc;
	unsigned char buf[512];
	struct ifreq *ifr;

	ifc.ifc_len = 512;
	ifc.ifc_buf = buf;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
		printf("socket error\n");
		return -1;
	}

	if(ioctl(fd, SIOCGIFCONF, &ifc) != 0){
		perror("ioctl error\n");
		return -1;
	}

	memset(cards_name, 0x0, buf_size);

	ifr = (struct ifreq*)buf;
	for(i=ifc.ifc_len/sizeof(struct ifreq); i> 0; i--, ifr++){
		if(!strcmp(ifr->ifr_name, "lo"))
			continue;

		ret = sprintf(cards_name, "%s%s,", cards_name, ifr->ifr_name);
		cnt++;
		if(ret >= buf_size)
			break;
	}
	cards_name[ret] = 0;
	return cnt;
}

int get_host_name(char* hostname){
	char host[256] = { 0 };
	if(gethostname(host, sizeof(host)) < 0){
		printf("gethostname error\n");
		return -1;
	}
	memcpy(hostname, host, sizeof(host));
	return 0;
}

int get_dns(char* dnsip){
	char* end = NULL;
	char* ret = NULL;
	char buf[linebuf] = { 0 };
	char path[32] = { "/etc/resolv.conf" };
	FILE* fp = fopen(path, "rb");
	while(!feof(fp) && fgets(buf, linebuf, fp) != NULL){
		if((ret = strstr(buf, "nameserver")) == NULL)
			continue;

		ret += strlen("nameserver");
		break;
	}
	fclose(fp);
	ret = ret + 1;
	end = ret+strlen(ret)-1;
	if(*end = '\n')
		*end = '\0';
	memcpy(dnsip, ret, 32);
	return 0;
}


int main(){
	netinfo ni;
	char dnsip[32] = { 0 };
	char cards_name[512] = { 0 };
	int cards = get_local_netcard_names(cards_name, sizeof(cards_name));
	printf("cards: %d\ncname: %s\n", cards, cards_name);
	get_local_netinfo_by_name("eth0", &ni);
	get_local_gateway_by_name("eth0", &ni);
	printf("ip:%s\n", ni.ip_addr);
	printf("mk:%s\n", ni.net_mask);
	printf("gw:%s\n", ni.gate_way);

	char hostname[256] = { 0 };
	get_host_name(hostname);
	printf("hn:%s\n", hostname);

	get_dns(dnsip);
	printf("dn:%s\n", dnsip);

	return 0;
	
}


