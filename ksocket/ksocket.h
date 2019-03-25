#ifndef __ksocket_h__
#define __ksocket_h__

struct socket* ksocket(int family, int type, int protocol);
int kconnect(struct socket* socket, struct sockaddr* address, int address_len);
int kbind(struct socket* socket, struct sockaddr* address, int address_len);
int klisten(struct socket* socket, int backlog);
struct socket* kaccept(struct socket* socket, struct sockaddr* address, int* address_len);
ssize_t ksend(struct socket* socket, const void* buffer, size_t buffer_len, int flags);
ssize_t krecv(struct socket* socket, void* buffer, size_t buffer_len, int flags);
int kclose(struct socket* socket);
int ksetsockopt(struct socket* socket, int level, int optname, void* optval, int optlen);
unsigned int inet_addr(char* ip);
char *inet_ntoa(struct in_addr *in);

#endif
