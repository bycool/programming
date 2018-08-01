/*
 *  * hello-mod.c
 *   * a kernel-space client example of relayfs filesystem
 *    */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

static struct rchan *hello_rchan;
int init_module(void)
{
        const char *msg="Hello world\n";
        hello_rchan = relay_open("cpu", NULL, 8192, 2, NULL, NULL);
        if(!hello_rchan){
                printk("relay_open() failed.\n");
                return -ENOMEM;
        }
        relay_write(hello_rchan, msg, strlen(msg));
        return 0;
}
void cleanup_module(void)
{
        if(hello_rchan) {
                relay_close(hello_rchan);
                hello_rchan = NULL;
        }
        return;
}
MODULE_LICENSE ("GPL");
MODULE_DESCRIPTION ("Simple example of Relay");
