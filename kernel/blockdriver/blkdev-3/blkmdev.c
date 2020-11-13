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

static void blkmdev_do_request(struct request_queue* q){
	struct request* req;
	struct req_iterator ri;
	struct bio_vec *bvec;
	char *disk_mem;
	char *buffer;

	while((req = blk_fetch_request(q)) != NULL){
		if((blk_rq_pos(req) << 9) + blk_rq_cur_bytes(req) > BLKMDEV_BYTES){
			printk(KERN_ERR BLKMDEV_DISKNAME ":bad request: blk=%llu, count=%u\n", (unsigned long long)blk_rq_pos(req), blk_rq_cur_bytes(req));
			__blk_end_request_all(req, -EIO);
			continue;
		}
		disk_mem = blkmdev_data + (blk_rq_pos(req) << 9);
		switch(rq_data_dir(req)){
			case READ:
				printk("blkmdev: READ\n");
				rq_for_each_segment(bvec, req, ri){
					buffer = kmap(bvec->bv_page) + bvec->bv_offset;
					memcpy(buffer, disk_mem, bvec->bv_len);
					kunmap(bvec->bv_page);
					disk_mem += bvec->bv_len;
				}
				__blk_end_request_all(req, 0);
				break;

			case WRITE:
				printk("blkmdev: WRITE\n");
				rq_for_each_segment(bvec, req, ri){
					buffer = kmap(bvec->bv_page) + bvec->bv_offset;
					memcpy(disk_mem, buffer, bvec->bv_len);
					kunmap(bvec->bv_page);
					disk_mem += bvec->bv_len;
				}
				__blk_end_request_all(req, 0);
				break;
			default:
				break;
		}
	}
}

struct block_device_operations blkmdev_fops = {
	.owner = THIS_MODULE,
};


static int __init init_blkmdev(void){
	int ret = -1;

	blkmdev_queue = blk_init_queue(blkmdev_do_request, NULL);
	if(!blkmdev_queue){
		ret = -ENOMEM;
		goto err_init_queue;
	}

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

err_init_queue:
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
