#include "bb.h"

typedef int bio_iter_t ;
typedef struct bio_vec* bio_iter_bvec_t ;

static make_request_fn* org_blk_mrf = NULL;
char rbio[64] ;

atomic_t mrf_used = ATOMIC_INIT(0) ;

#define bio_iter_len(bio, iter) ((bio)->bi_io_vec[(iter)].bv_len)
#define bio_iter_offset(bio, iter) ((bio)->bi_io_vec[(iter)].bv_offset)

static int new_blk_mrf(struct request_queue *q, struct bio* bio) {
	int ret;
	char ddname[16] ;
	char rules[32] ;
	struct bio_vec* bvec ;
	bio_iter_t iter ;

	bdevname(bio->bi_bdev, ddname) ;

	bio_for_each_segment(bvec, bio, iter)
	{
		switch(bio_rw(bio)) {
			case WRITE:
				ret = bbfilter(ddname, bio->bi_sector, rules) ;
				if(ret) {
					sprintf(rbio, "%lu,%d%s", bio->bi_sector, bio_iter_len(bio, iter), rules) ;
					bb_relay_write(rbio, strlen(rbio)) ;
				}
				break ;
			default:
				break ;
		}
	}

	ret = org_blk_mrf(q, bio) ;

	return ret ;
}


static struct block_device* bbdev_getblkdev_bypath(const char* devpath, fmode_t mode) {
	int ret ;
	struct block_device* bdev ;
	struct nameidata nd ;
	struct inode* binode ;
	dev_t dev;

	if((ret = path_lookup(devpath, LOOKUP_FOLLOW, &nd))) {
		bdev = ERR_PTR(ret);
		return bdev;
	}

	binode = nd.path.dentry->d_inode;
	if(!binode) {
		ret = -ENOENT ;
		bdev = ERR_PTR(ret) ;
		return bdev ;
	}

	if(!S_ISBLK(binode->i_mode)) {
		ret = -ENOTBLK ;
		bdev = ERR_PTR(ret) ;
		return bdev ;
	}

	dev = binode->i_rdev ;
	bdev = open_by_devnum(dev, mode) ; // hold block_device struct

	path_put(&nd.path) ;

	return bdev ;
}

#if 0
static void set_blk_mrf(struct block_device* bdev) {
	struct request_queue* q = bdev_get_queue(bdev) ;
	struct super_block* sb ;

	fsync_bdev(bdev) ;
	sb = freeze_bdev(bdev) ;

	if(q->make_request_fn != new_blk_mrf) {
		org_blk_mrf = q->make_request_fn ;
		q->make_request_fn = new_blk_mrf;
	}
	thaw_bdev(bdev, sb) ;
}

static void reset_blk_mrf(struct block_device* bdev) {
	struct request_queue* q = bdev_get_queue(bdev) ;
	struct super_block* sb ;

	fsync_bdev(bdev) ;
	sb = freeze_bdev(bdev) ;

	if(org_blk_mrf!=NULL) {
		while(atomic_read(&mrf_used)!=0) {
			printk("wait for reset: %d\n", atomic_read(&mrf_used)) ;
			msleep(5) ;
		}
		printk("reset blk mrf: %s\n", bdev->bd_disk->disk_name) ;
		q->make_request_fn = org_blk_mrf ;
	}

	thaw_bdev(bdev, sb);
}
#endif 

int bbdev_setblk_mrf_bypath(const char* devpath) {
	struct block_device* bdev ;
	struct super_block* sb ;
	struct request_queue* q;

	if((bdev = bbdev_getblkdev_bypath(devpath, FMODE_READ))==NULL) {
		printk("bbdev_setblk_mrf_bypath [get_blk_dev fail]\n") ;
		return -1 ;
	}
	q = bdev_get_queue(bdev) ;

	fsync_bdev(bdev) ;
	sb = freeze_bdev(bdev) ;

	if(q->make_request_fn != new_blk_mrf) {
		org_blk_mrf = q->make_request_fn ;
		q->make_request_fn = new_blk_mrf ;
	}

	thaw_bdev(bdev, sb) ;
	blkdev_put(bdev, FMODE_READ) ;
	return 0 ;
}

int bbdev_resetblk_mrf_bypath(const char* devpath) {
	struct block_device* bdev ;
	struct super_block* sb ;
	struct request_queue* q ;

	if((bdev = bbdev_getblkdev_bypath(devpath, FMODE_READ))==NULL) {
		printk("bbdev_resetblk_mrf_bypath [get_blk_dev fail]\n") ;
		return -1 ;
	}
	q = bdev_get_queue(bdev) ;

	fsync_bdev(bdev) ;
	sb = freeze_bdev(bdev) ;

	if(org_blk_mrf!=NULL) {
		while(atomic_read(&mrf_used)!=0) {
			printk("wait for reset: %d\n", atomic_read(&mrf_used)) ;
			msleep(5) ;
		}
		q->make_request_fn = org_blk_mrf ;
	}

	thaw_bdev(bdev, sb) ;
	blkdev_put(bdev, FMODE_READ) ;
	return 0 ;
}

int bbdev_get_devinfo(char* devpath, int* major, int* first_minor, int* partno, 
							char* disk_name, unsigned long* sector_s, unsigned long* sector_e) {
	int i ;
	char* p ;
	struct block_device* bdev ;
	struct hd_struct** hds_tbl ;

	bdev = bbdev_getblkdev_bypath(devpath, FMODE_READ) ;
	if(!bdev) {
		printk("open %s block device fail\n", devpath) ;
		return -1 ;
	}
	*major = bdev->bd_disk->major ;
	*first_minor = bdev->bd_disk->first_minor ;
	strcpy(disk_name, bdev->bd_disk->disk_name) ;

	p = strstr(devpath, disk_name) ;
	p += strlen(disk_name) ;
	i = p - devpath ;
	if(i==strlen(devpath))
		*partno = 0;
	else
		sscanf(p, "%d", partno) ;

	printk("gendisk: .name: %s .major: %d\n", bdev->bd_disk->disk_name ,bdev->bd_disk->major);
//	printk("part0.partno: %d, start_sect: %lu, nr_sects: %lu\n", bdev->bd_disk->part0.partno, bdev->bd_disk->part0.start_sect, bdev->bd_disk->part0.nr_sects);
	printk("disk_part_tbl.len : %d\n", bdev->bd_disk->part_tbl->len);


	hds_tbl = bdev->bd_disk->part_tbl->part ;
	for(i=0; i<bdev->bd_disk->part_tbl->len; i++) {
		if(!hds_tbl[i])
			continue ;

		if(hds_tbl[i]->partno == *partno)
		{
			*sector_s = hds_tbl[i]->start_sect ;
			*sector_e = hds_tbl[i]->start_sect + hds_tbl[i]->nr_sects ;
		}
		printk("part[%d],disk.major: %d, first_minor: %d,  partno: %d,  start_sect: %lu, nr_sector: %lu\n", i, bdev->bd_disk->major, bdev->bd_disk->first_minor, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);
	}

	blkdev_put(bdev, FMODE_READ) ;

	return 0 ;
}

#if 0
int __init bbdev_init(void){
	printk("[bbdev_init]\n");
    return 0;
}

void __exit bbdev_exit(void){
	printk("[bbdev_exit]\n");
}

module_init(bbdev_init);
module_exit(bbdev_exit);

MODULE_LICENSE("GPL");
#endif
