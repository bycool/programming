/*
 * Here's a sample kernel module showing the use of jprobes to dump
 * the arguments of do_fork().
 *
 * For more information on theory of operation of jprobes, see
 * Documentation/kprobes.txt
 *
 * Build and insert the kernel module as done in the kprobe example.
 * You will see the trace data in /var/log/messages and on the
 * console whenever do_fork() is invoked to create a new process.
 * (Some messages may be suppressed if syslogd is configured to
 * eliminate duplicate messages.)
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/spinlock.h>

#include <linux/sched.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/hdreg.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>


/*
 * Jumper probe for do_fork.
 * Mirror principle enables access to arguments of the probed routine
 * from the probe handler.
 */

/* Proxy routine having the same arguments as actual do_open() routine
static struct file *jsys_open(char *name, int flags){
	printk("jprobe: name: %s\n", name);
	jprobe_return();
	return NULL;
}
*/

/* Proxy routine having the same arguments as actual do_fork() routine 
static long jdo_fork(unsigned long clone_flags, unsigned long stack_start,
	      struct pt_regs *regs, unsigned long stack_size,
	      int __user *parent_tidptr, int __user *child_tidptr)
{
	printk(KERN_INFO "jprobe: clone_flags = 0x%lx, stack_size = 0x%lx,"
			" regs = 0x%p\n",
	       clone_flags, stack_size, regs);

	* Always end with a call to jprobe_return(). *
	jprobe_return();
	return 0;
}
*/

/* Proxy routine having the same arguments as actual submit_bio() routine */
static void jprobe_submit_bio(int rw, struct bio *bio){
	struct bio_vec* bvec;
	int i;

	char dname[128];
	bdevname(bio->bi_bdev, dname);
	printk("device:name: %s\n", dname);
	bio_for_each_segment(bvec, bio, i){
		switch(bio_rw(bio)){
			case READ:
				printk("READ :%d\n", bvec->bv_len);
				break;
			case WRITE:
				printk("WRITE : %d\n", bvec->bv_len);
				break;

			default:
				break;
		}
	}

	jprobe_return();
}

static struct jprobe my_jprobe = {
	.entry			= jprobe_submit_bio,
	.kp = {
		.symbol_name	= "submit_bio",
	},
};

static int __init jprobe_init(void)
{
	int ret;

	ret = register_jprobe(&my_jprobe);
	if (ret < 0) {
		printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
		return -1;
	}
	printk(KERN_INFO "Planted jprobe at %p, handler addr %p\n",
	       my_jprobe.kp.addr, my_jprobe.entry);
	return 0;
}

static void __exit jprobe_exit(void)
{
	unregister_jprobe(&my_jprobe);
	printk(KERN_INFO "jprobe at %p unregistered\n", my_jprobe.kp.addr);
}

module_init(jprobe_init)
module_exit(jprobe_exit)
MODULE_LICENSE("GPL");
