/*
 * audience.c
 * a user-space client example of relayfs filesystem
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#define MAX_BUFLEN 256
const char filename_base[]="/mnt/relay/cpu";
// implement your own get_cputotal() before compilation
static int get_cputotal(void);
int main(void)
{
        char filename[128]={0};
        char buf[MAX_BUFLEN];
        int fd, c, i, bytesread, cputotal = 0;
        if(mount("relayfs", "/mnt/relay", "relayfs", 0, NULL)
                        && (errno != EBUSY)) {
                printf("mount() failed: %s/n", strerror(errno));
                return 1;
        }
        cputotal = get_cputotal();
        if(cputotal <= 0) {
                printf("invalid cputotal value: %d/n", cputotal);
                return 1;
        }
        for(i=0; i<cputotal; i++) {
                // open per-cpu file
                sprintf(filename, "%s%d", filename_base, i);
                fd = open(filename, O_RDONLY);
                if (fd < 0) {
                        printf("fopen() failed: %s/n", strerror(errno));
                        return 1;
                }
                // read per-cpu file
                bytesread = read(fd, buf, MAX_BUFLEN);
                while(bytesread > 0) {
                        buf[bytesread] = '/0';
                        puts(buf);
                        bytesread = read(fd, buf, MAX_BUFLEN);
                };
                // close per-cpu file
                if(fd > 0) {
                        close(fd);
                        fd = 0;
                }
        }
        if(umount("/mnt/relay") && (errno != EINVAL)) {
                printf("umount() failed: %s/n", strerror(errno));
                return 1;
        }
        return 0;
}

