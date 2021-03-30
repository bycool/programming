#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/file.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/dcache.h>
#include <linux/sched.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/namei.h>
#include <linux/nfs_fs.h>
#include <linux/audit.h>
#include <linux/mount.h>
#include <linux/fs_struct.h>
#include <linux/limits.h>
#include <linux/unistd.h>
#include <linux/genhd.h>

struct task_struct * dssndu = NULL;
struct task_struct * dud = NULL;

char* path1 = "/home/ten/1.txt";

static int display_sb_sndu(void* data){
	struct super_block *sb = (struct super_block*)data;
	while(!kthread_should_stop()){
		printk("sb->sndu: %d\n", sb->s_nr_dentry_unused);
		msleep(1000);
	}
	return 0;
}

static int display_unused_dentry(void* data){
	struct dentry* dy = NULL;
	struct super_block *sb = (struct super_block*)data;
	while(!kthread_should_stop()){
		list_for_each_entry(dy, &sb->s_dentry_lru, d_lru){
			if(dy->d_inode == NULL)
				dput(dy);
//				printk("dentry.name: %s\n", dy->d_name.name);
		}
		msleep(1000);
	}
	return 0;
}

static int __init callsys_init(void){
	struct file *pfile = NULL;
	struct dentry *pden = NULL;
	struct super_block* sb = NULL;

	printk("[callsys_init]\n");

	pfile = filp_open(path1, O_RDONLY, 0640);
	if(!pfile){
		printk("filp_open error\n");
		return 0;
	}

	pden = pfile->f_path.dentry;
	sb = pden->d_sb;

	dssndu = kthread_create(display_sb_sndu, (void*)sb, "dssndu");
	if (!IS_ERR(dssndu))
		wake_up_process(dssndu);

//	dud = kthread_create(display_unused_dentry, (void*)sb, "dud");
//	if (!IS_ERR(dud))
//		wake_up_process(dud);

	return 0;
}

static void __exit callsys_exit(void){
	if(dssndu->state != TASK_DEAD)
		kthread_stop(dssndu);

	if(dud->state != TASK_DEAD)
		kthread_stop(dud);
	printk("[callsys_exit]\n");
}

module_init(callsys_init);
module_exit(callsys_exit);

MODULE_LICENSE("GPL");

