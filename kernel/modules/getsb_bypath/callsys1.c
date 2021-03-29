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

char* path1 = "/mnt/sdb/bb.ko";
char* path2 = "/mnt/sdc/bbackup.c";
char* path3 = "/home/ten/blockbackup/";


static int __init callsys_init(void){
	struct file* pfile = NULL;
	struct dentry *pdentry = NULL;
	struct super_block* sb = NULL;
	struct block_device* bdev = NULL;
	printk("[callsys_init]\n");


	pfile = filp_open(path2, O_RDWR, 0640);
	if(!pfile){
		printk("filp_open fail\n");
		return 0;
	}

	pdentry = pfile->f_path.dentry;
	printk("name: %s\n", pdentry->d_name.name);

	sb = pdentry->d_sb;
	bdev = sb->s_bdev;

		printk("diskname: %s\n", bdev->bd_disk->disk_name);

	filp_close(pfile, NULL);

	return 0;
}

static void __exit callsys_exit(void){
	printk("[callsys_exit]\n");
}

module_init(callsys_init);
module_exit(callsys_exit);

MODULE_LICENSE("GPL");

