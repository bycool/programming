#include <linux/module.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/types.h>
#include <linux/genhd.h>


static struct block_device* binfo_getblkdev_bypath(const char* devpath, fmode_t mode){
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

	gbb_dev = binfo_getblkdev_bypath(devpath, FMODE_READ);
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
		printk("part[%d],disk.major: %d, first_minor: %d,  partno: %d,  start_sect: %lu, nr_sector: %lu\n", i, gbb_dev->bd_disk->major, gbb_dev->bd_disk->first_minor, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);
	}

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
