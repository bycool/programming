#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/types.h>
#include <linux/genhd.h>

const char* gbdev = "/dev/sdc";
struct block_device* gbb_dev = NULL;


static struct block_device* binfo_getblkdev_bypath(const char* dpath, fmode_t mode){
	int ret;
	struct block_device* bdev;
	struct nameidata nd;
	struct inode* binode;
	dev_t dev;

	if((ret = path_lookup(gbdev, LOOKUP_FOLLOW, &nd))){
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

int __init binfo_init(void){
	int i = 0;
	struct hd_struct ** hds_tbl;
	printk("----------------- block info init --------------------\n");

	gbb_dev = binfo_getblkdev_bypath(gbdev, FMODE_READ);
	if(!gbb_dev)
		printk("open %s block device fail\n", gbdev);

	printk("gendisk.major: %d\n", gbb_dev->bd_disk->major);

	hds_tbl = gbb_dev->bd_disk->part_tbl->part;
	for(i=0; hds_tbl[i]  ;i++){
		printk("part[%d],disk.major: %d, partno: %d,  start_sect: %lu, nr_sector: %d\n", i+1, gbb_dev->bd_disk->major, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);
	}

	
	return 0;
}

void __exit binfo_exit(void){
	printk("----------------- block info exit --------------------\n");

	if(gbb_dev)
		blkdev_put(gbb_dev, FMODE_READ);
}

module_init(binfo_init);
module_exit(binfo_exit);

MODULE_LICENSE("GPL");
