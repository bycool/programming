#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/types.h>
#include <linux/genhd.h>

typedef int bio_iter_t;
typedef struct bio_vec *bio_iter_bvec_t;

static make_request_fn * org_blk_mrf = NULL;
static char ddname[16];

atomic_t mrf_used = ATOMIC_INIT(0);

#define bio_iter_len(bio, iter) ((bio)->bi_io_vec[(iter)].bv_len)
#define bio_iter_offset(bio, iter) ((bio)->bi_io_vec[(iter)].bv_offset)

static int new_mrf(struct request_queue *q, struct bio *bio) {
    int ret = -1;
    struct bio_vec *bvec ;
    bio_iter_t iter;
    bdevname(bio->bi_bdev, ddname);
    atomic_add(1, &mrf_used);
    bio_for_each_segment(bvec, bio, iter) {
        switch(bio_rw(bio)){
        case READ :
        case READA :
            break ;
        case WRITE :
            printk("WRITE::name: %s, len: %u ,offset: %d ,start_sector: %lu,end_sector: %lu\n", ddname, bio_iter_len(bio, iter), bio_iter_offset(bio, iter), bio->bi_sector, bio->bi_sector + bio_iter_len(bio, iter) / 512 - 1 );
            break;

        default:
            break;
        }
    }
    ret = org_blk_mrf(q, bio) ;
    atomic_sub(1, &mrf_used);
    return ret;
}

static int set_blk_mrf(struct block_device *bdev) {
    struct request_queue * q = bdev_get_queue(bdev) ;
    struct super_block *sb ;
	printk("set blk_mrf\n");
    if(q->make_request_fn != new_mrf) {
        org_blk_mrf = q->make_request_fn ;
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

    if(org_blk_mrf) {
        while(atomic_read(&mrf_used)!=0){
            printk("reset: %d\n", atomic_read(&mrf_used));
            msleep(5);
        }
        fsync_bdev(bdev) ;
        sb = freeze_bdev(bdev) ;
        q->make_request_fn = org_blk_mrf ;
        thaw_bdev(bdev,sb) ;
    }
}



static struct block_device* bbdev_getblkdev_bypath(const char* devpath, fmode_t mode){
	int ret;
	struct block_device* bdev;
	struct nameidata nd;
	struct inode* binode;
	dev_t dev;

	if((ret = path_lookup(devpath, LOOKUP_FOLLOW, &nd))){
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

int bbdev_get_devinfo(char* devpath, int* major, int* first_minor, int* partno, char* disk_name, unsigned long* sector_s, unsigned long* sector_e){
	int i = 0;
	char* p = NULL;
	struct block_device* gbb_dev = NULL;
	struct hd_struct ** hds_tbl;

	gbb_dev = bbdev_getblkdev_bypath(devpath, FMODE_READ);
	if(!gbb_dev) {
		printk("open %s block device fail\n", devpath);
		return 1;
	}
	*major = gbb_dev->bd_disk->major;
	*first_minor = gbb_dev->bd_disk->first_minor;
	strcpy(disk_name, gbb_dev->bd_disk->disk_name);
	p = strstr(devpath, disk_name);
	p += strlen(disk_name);
	sscanf(p, "%d", partno);

//	printk("gendisk: .name: %s .major: %d\n", gbb_dev->bd_disk->disk_name ,gbb_dev->bd_disk->major);
//	printk("part0.partno: %d, start_sect: %lu, nr_sects: %lu\n", gbb_dev->bd_disk->part0.partno, gbb_dev->bd_disk->part0.start_sect, gbb_dev->bd_disk->part0.nr_sects);

//	printk("disk_part_tbl.len : %d\n", gbb_dev->bd_disk->part_tbl->len);

	hds_tbl = gbb_dev->bd_disk->part_tbl->part;
	for(i=0; i<gbb_dev->bd_disk->part_tbl->len  ;i++){
		if(!hds_tbl[i]){
			continue;
		}
	if(hds_tbl[i]->partno == *partno)
	{
		*sector_s = hds_tbl[i]->start_sect;
		*sector_e = hds_tbl[i]->start_sect + hds_tbl[i]->nr_sects;
	}
//		printk("part[%d],disk.major: %d, first_minor: %d,  partno: %d,  start_sect: %lu, nr_sector: %lu\n", i, gbb_dev->bd_disk->major, gbb_dev->bd_disk->first_minor, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);
	}

//printk("major: %d\n", *major);

	blkdev_put(gbb_dev, FMODE_READ);

	return 0;
}

int bbdev_hook_mrf(char* devpath) {
	int ret ;
	struct block_device* gbb_dev = bbdev_getblkdev_bypath(devpath, FMODE_READ);
	if(gbb_dev == NULL){
		printk("hook mrf get blk fail\n");
		return 1;
	}
	ret = set_blk_mrf(gbb_dev);
	blkdev_put(gbb_dev, FMODE_READ);
	return 0;
}

int bbdev_unhook_mrf(char* devpath) {
	struct block_device* gbb_dev = bbdev_getblkdev_bypath(devpath, FMODE_READ);
	if(gbb_dev == NULL){
		printk("hook mrf get blk fail\n");
		return 1;
	}
	reset_blk_mrf(gbb_dev);
	blkdev_put(gbb_dev, FMODE_READ);
	return 0;
}

#if 0
int __init bbdev_init(void){
	char bdevpath[32] = "/dev/sdd2";
	int bmajor;
	int bfirst_minor;
	int bpartno;
	char bdisk_name[32];
	unsigned long bs;
	unsigned long be;

	bbdev_get_devinfo(bdevpath, &bmajor, &bfirst_minor, &bpartno, bdisk_name, &bs, &be);
	printk("path        : %s\n", bdevpath);
	printk("major       : %d\n", bmajor);
	printk("first_minor : %d\n", bfirst_minor);
	printk("partno      : %d\n", bpartno);
	printk("disk_name   : %s\n", bdisk_name);
	printk("sector_s    : %lu\n", bs);
	printk("sector_e    : %lu\n", be);
	return 0;
}

void __exit bbdev_exit(void){

}

module_init(bbdev_init);
module_exit(bbdev_exit);

MODULE_LICENSE("GPL");

#endif
