#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mount.h>
#include <linux/buffer_head.h>
#include <linux/unistd.h>
#include <linux/vmalloc.h>
#include <linux/random.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <linux/string.h>



const char* dname = "/dev/sda3" ;

struct block_device * bdev = NULL ;
struct super_block *  bsuperblk = NULL;;
//struct request_queue * cq;



static struct block_device* superinfo_get_bld_by_path(const char* bpath, fmode_t mode){
	int ret;
	struct block_device *bdev;
	struct nameidata nd;
	struct inode* binode;
	dev_t dev;

	if((ret = path_lookup(bpath, LOOKUP_FOLLOW, &nd))){
		bdev = ERR_PTR(ret);
		return bdev;
	}

	binode = nd.path.dentry->d_inode;
	if(!binode){
		ret = -ENOENT;
		bdev = ERR_PTR(ret);
		return bdev;
	}

	if(!S_ISBLK(binode->i_mode)){
		ret = -ENOTBLK;
		bdev = ERR_PTR(ret);
		return bdev;
	}

	dev = binode->i_rdev;
	bdev = open_by_devnum(dev, mode);

	path_put(&nd.path);

	return bdev;
}


static int __init superinfo_init(void){
//	struct list_head *iter;
	struct file* file;
	printk("=================== superinfo_init ==================\n");

	bdev = superinfo_get_bld_by_path(dname, FMODE_READ);
	if(!bdev)
		printk("open %s fail\n", dname);

	bsuperblk = bdev->bd_super;
	if(!bsuperblk){
		printk("superblk is null\n");
	}
	if(!bsuperblk->s_bdev)
		printk("bsuperblk->s_bdev is null\n");

	if(bsuperblk->s_bdev == bdev)
		printk("superblk-s_dev == bdev\n");

/*
	list_for_each(iter, &bsuperblk->s_inodes){
		struct inode *inode = list_entry(iter, struct inode, i_sb_list);
		printk("inode.no: %lu\n", inode->i_ino);
	}
*/

	printk("superblock.s_blocksize: %lu\n", bsuperblk->s_blocksize);
	printk("superblock.s_blocksize_bits: %d\n", bsuperblk->s_blocksize_bits);
	printk("superblock.s_maxbytes: %llu\n", bsuperblk->s_maxbytes);
	printk("superblock.s_root: %s\n", bsuperblk->s_root->d_name.name);

	printk("superblock.s_id: %s\n", bsuperblk->s_id);

	printk("dev/sdb1 file_system_type: %s\n", bsuperblk->s_type->name);

	list_for_each_entry(file, &bsuperblk->s_files, f_u.fu_list) {
		struct dentry* dentry = file->f_path.dentry;
		printk("opening.file.name: %s\n", dentry->d_name.name);
	}




	return 0;
}

static void __exit superinfo_exit(void){
	if(bdev)
		blkdev_put(bdev, FMODE_READ);

	printk("=================== superinfo_exit ==================\n");
}

module_init(superinfo_init);
module_exit(superinfo_exit);

MODULE_LICENSE("GPL");
