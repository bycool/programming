#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mount.h>
#include <linux/buffer_head.h>
#include <linux/namei.h>
#include <linux/unistd.h>
#include <linux/vmalloc.h>
#include <linux/random.h>

const char* dname = "/dev/sdb1" ;
const char* cname = "/dev/sdc1" ;

struct block_device * bdev = NULL ;
struct block_device * cdev = NULL ;

struct request_queue * cq;

make_request_fn * blk_org_mrf ;
make_request_fn * cblk_org_mrf ;

static int new_mrf(struct request_queue *q, struct bio *bio) {
//	struct bio_vec *bvec ;
//	int i ;
	void* cbio = kmalloc(bio->bi_size, GFP_KERNEL);
	bio_copy_kern(q, cbio, bio->bi_size, GFP_KERNEL, READ);
	printk("cbio.size: %u\n", ((struct bio*)cbio)->bi_size);
	printk("bio.size: %u\n", bio->bi_size);
//	cblk_org_mrf(cq, cbio);
/*	bio_for_each_segment(bvec, bio, i) {
		switch(bio_rw(bio)){
		case READ :
		case READA :
			printk("read bio: [page: %p | len: %u | offset: %u]\n", bvec->bv_page, bvec->bv_len, bvec->bv_offset) ;
			break ;
		case WRITE :
			printk("write bio: [page: %p | len: %u | offset: %u]\n", bvec->bv_page, bvec->bv_len, bvec->bv_offset) ;
			break;

		default:
			break;
		}
	}
*/
	return blk_org_mrf(q, bio) ;
}

static int get_cblk_mrf(struct block_device *bdev) {
	cq = bdev_get_queue(bdev) ;
	if(cq) printk("get sdc1 request queue ok\n");
	cblk_org_mrf = cq->make_request_fn ;
	cq->make_request_fn = NULL ;
	if(cblk_org_mrf) printk("get sdc1 mrf ok\n");
	return 0;
}

static int set_blk_mrf(struct block_device *bdev) {
	struct request_queue * q = bdev_get_queue(bdev) ;
	struct super_block *sb ;

	if(q->make_request_fn != new_mrf) {
		blk_org_mrf = q->make_request_fn ;
		fsync_bdev(bdev) ;
		sb = freeze_bdev(bdev) ;
		q->make_request_fn = new_mrf ;
		thaw_bdev(bdev,sb) ;
		return 0 ;
	}
	return -1 ;
}

static void reset_blk_mrf(struct block_device *bdev) {
	struct request_queue *q = bdev_get_queue(bdev) ;
    struct super_block *sb = NULL ;

	if(blk_org_mrf) {
		fsync_bdev(bdev) ;
		sb = freeze_bdev(bdev) ;
		q->make_request_fn = blk_org_mrf ;
		thaw_bdev(bdev,sb) ;
	}
}



static struct block_device* incmon_get_bld_by_path(const char* bpath, fmode_t mode){
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




static int __init incmon_init(void){
	int ret = -1;
	bdev = incmon_get_bld_by_path(dname, FMODE_READ);
	cdev = incmon_get_bld_by_path(cname, FMODE_READ);
	if(!bdev)
		printk("open %s fail\n", dname);

	ret = set_blk_mrf(bdev);
	get_cblk_mrf(cdev);
	if(ret == 0)
		printk("hook ok\n");

	printk("incmon_init\n");
	return 0;
}

static void __exit incmon_exit(void){
	reset_blk_mrf(bdev);

	if(bdev)
		blkdev_put(bdev, FMODE_READ);
	printk("incmon_exit\n");
}

module_init(incmon_init);
module_exit(incmon_exit);

MODULE_LICENSE("GPL");
