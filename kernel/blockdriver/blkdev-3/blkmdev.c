/*
 * block disk (on raw) driver, kernel_version > 2.6.31
 */

#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/bio.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/genhd.h>

#define BLKMDEV_DEVICEMAJOR	COMPAQ_SMART2_MAJOR
#define BLKMDEV_DISKNAME	"blkmdev"
#define BLKMDEV_BYTES		(16 * 1024 * 1024)

unsigned char blkmdev_data[BLKMDEV_BYTES];

static struct gendisk *blkmdev_disk;
static struct request_queue *blkmdev_queue;

static int blkmdev_make_request(struct request_queue* q, struct bio* bio){
	struct bio_vec* bvec;
	int i ;
	void *dsk_mem;

	if((bio->bi_sector << 9) + bio->bi_size > BLKMDEV_BYTES){
		printk(KERN_ERR BLKMDEV_DISKNAME ":bad request: block=%llu, count=%u\n", (unsigned long long)bio->bi_sector, bio->bi_size);
		bio_endio(bio, -EIO);
		return 0;
	}

	dsk_mem = blkmdev_data + (bio->bi_sector << 9);

	bio_for_each_segment(bvec, bio, i){
		void *iovec_mem;
		switch(bio_rw(bio)){
			case READ:
			case READA:
//				printk("blkmdev:READ:%d\n", bvec->bv_len);
				iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(iovec_mem, dsk_mem, bvec->bv_len);
				kunmap(bvec->bv_page);
				break;
			case WRITE:
				printk("blkmdev:WRITE:%d\n", bvec->bv_len);
				iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(dsk_mem, iovec_mem, bvec->bv_len);
				kunmap(bvec->bv_page);
				break;
			default:
				printk(KERN_ERR BLKMDEV_DISKNAME ":unknown value of bio_rw: %lu\n", bio_rw(bio));
				bio_endio(bio, -EIO);
				return 0;
		}
		dsk_mem += bvec->bv_len;
	}
	bio_endio(bio, 0);
	return 0;
}

struct block_device_operations blkmdev_fops = {
	.owner = THIS_MODULE,
};


static int __init init_blkmdev(void){
	int ret = -1;

	blkmdev_queue = blk_alloc_queue(GFP_KERNEL);
	if(!blkmdev_queue){
		ret = -ENOMEM;
		goto err_alloc_queue;
	}
	blk_queue_make_request(blkmdev_queue, blkmdev_make_request);

	blkmdev_disk = alloc_disk(1);
	if(!blkmdev_disk){
		ret = -ENOMEM;
		goto err_alloc_disk;
	}
	strcpy(blkmdev_disk->disk_name, BLKMDEV_DISKNAME);
	blkmdev_disk->major = BLKMDEV_DEVICEMAJOR;
	blkmdev_disk->first_minor = 0;
	blkmdev_disk->fops = &blkmdev_fops;
	blkmdev_disk->queue = blkmdev_queue;
	set_capacity(blkmdev_disk, BLKMDEV_BYTES >> 9);
	add_disk(blkmdev_disk);

	printk("---------- init_blkmdev ----------\n");
	return 0;

err_alloc_disk:
	blk_cleanup_queue(blkmdev_queue);

err_alloc_queue:
	return ret;
}

static void __exit exit_blkmdev(void){
	
	del_gendisk(blkmdev_disk);
	put_disk(blkmdev_disk);
	blk_cleanup_queue(blkmdev_queue);
	printk("---------- exit_blkmdev ----------\n");
}

module_init(init_blkmdev);
module_exit(exit_blkmdev);

MODULE_LICENSE("GPL");
