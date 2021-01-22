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

#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#include <linux/relay.h>
#include <linux/debugfs.h>

struct mnode {
    int major;
    int first_minor;
    int partno;
    char disk_name[DISK_NAME_LEN];
	make_request_fn* blk_org_mrf;
    unsigned long sector_start;
    unsigned long sector_end;
};

const char* dname = "/dev/sdb1" ;
const char* dname1 = "/dev/sdc1" ;
static char ddname[16];

//static char rbio[16];
struct block_device * bdev = NULL ;
make_request_fn * blk_org_mrf ;
struct request_queue * cq;

struct mnode sdbm;
struct mnode sdcm;

atomic_t mrf_used = ATOMIC_INIT(0);


#if 0
struct sock *nl_sk = NULL;
u32 user_pid = 0;
#define NETLINK_SOCKNO 22
#endif

typedef int bio_iter_t;
typedef struct bio_vec *bio_iter_bvec_t;
#define bio_iter_len(bio, iter) ((bio)->bi_io_vec[(iter)].bv_len)
#define bio_iter_offset(bio, iter) ((bio)->bi_io_vec[(iter)].bv_offset)
#if 0
#define bio_iter_page(bio, iter) ((bio)->bi_io_vec[(iter)].bv_page)
#define bio_iter_idx(iter) (iter)
#define bio_sector(bio) (bio)->bi_sector
#define bio_size(bio) (bio)->bi_size
#define bio_idx(bio) (bio)->bi_idx
#else
#define bio_iovec_idx(bio, idx) (&((bio)->bi_io_vec[(idx)]))
#define bio_iovec(bio)      bio_iovec_idx((bio), (bio)->bi_idx)
#define bio_page(bio)       bio_iovec((bio))->bv_page
#define bio_offset(bio)     bio_iovec((bio))->bv_offset
#define bio_segments(bio)   ((bio)->bi_vcnt - (bio)->bi_idx)
#define bio_sectors(bio)    ((bio)->bi_size >> 9)
#define bio_empty_barrier(bio)  (bio_rw_flagged(bio, BIO_RW_BARRIER) && !bio_has_data(bio) && !bio_rw_flagged(bio, BIO_RW_DISCARD))
#endif

static struct rchan *relay_rchan = NULL;

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
//			printk("READA::len: %u ,offset: %d ,start_sector: %lu,end_sector: %lu\n", bio_iter_len(bio, iter), bio_iter_offset(bio, iter), bio->bi_sector, bio->bi_sector + bio_iter_len(bio, iter) / 512 - 1 );
//			printk("read : [page: %p | len: %u | offset: %u]\n", bvec->bv_page, bvec->bv_len, bvec->bv_offset) ;
//			printk("read dev:%s: sector: %lu, [page: %p | len: %u | offset: %u]\n", ddname, bio->bi_sector, bvec->bv_page, bvec->bv_len, bvec->bv_offset) ;
			break ;
		case WRITE :
			printk("WRITE::name: %s, len: %u ,offset: %d ,start_sector: %lu,end_sector: %lu\n", ddname, bio_iter_len(bio, iter), bio_iter_offset(bio, iter), bio->bi_sector, bio->bi_sector + bio_iter_len(bio, iter) / 512 - 1 );
//			sprintf(rbio, "%lu,%u", bio->bi_sector, bio_iter_len(bio, iter));
//			relay_write(relay_rchan, rbio, strlen(rbio));
//			printk("write [page: %p | len: %u | offset: %u]\n",  bvec->bv_page, bvec->bv_len, bvec->bv_offset) ;
//			printk("write dev: %s: sector: %lu, size: %u\n", ddname, bio->bi_sector, bio->bi_size) ;
			break;

		default:
			break;
		}
	}
	ret = sdbm.blk_org_mrf(q, bio) ;
	atomic_sub(1, &mrf_used);
	return ret;
}

static int get_blk_mrf(struct block_device *bdev){
	struct request_queue * q = bdev_get_queue(bdev) ;
	printk("q %p\n", (void*)q);
	printk("q->make_request_fn: %p\n", q->make_request_fn);
	return 0;
}

static int set_blk_mrf(struct block_device *bdev, make_request_fn** blk_org_mrf) {
	struct request_queue * q = bdev_get_queue(bdev) ;
	struct super_block *sb ;

	if(q->make_request_fn != new_mrf) {
		*blk_org_mrf = q->make_request_fn ;
		printk("block_org_mrf: %p\n", *blk_org_mrf);
		fsync_bdev(bdev) ;
		sb = freeze_bdev(bdev) ;
		q->make_request_fn = new_mrf ;
		thaw_bdev(bdev,sb) ;
		return 0 ;
	}
	return -1 ;
}

static void reset_blk_mrf(struct block_device *bdev, make_request_fn* blk_org_mrf) {
	struct request_queue *q = bdev_get_queue(bdev) ;
    struct super_block *sb = NULL ;

	if(blk_org_mrf) {
		while(atomic_read(&mrf_used)!=0){
			printk("reset: %d\n", atomic_read(&mrf_used));
			msleep(5);
		}
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

//======================= relayfs ====================================
static void buf_mapped_callback(struct rchan_buf *buf,struct file* pfile){
    printk("buf_mapped_callback\n");
}

static void buf_unmapped_callback(struct rchan_buf* rbuf, struct file* pfile){
    printk("buf_unmapped_callback\n");
}

static struct dentry * create_buf_file_callback(const char *filename, struct dentry *parent, int mode, struct rchan_buf *buf, int *is_global)
{
    *is_global = 1;
    return debugfs_create_file(filename, mode, parent, buf, &relay_file_operations);
}

static int remove_buf_file_callback(struct dentry *dentry)
{
    printk("dentry remove!\n");
    debugfs_remove(dentry);
    return 0;
}

static struct rchan_callbacks relay_callbacks =
{
    .buf_mapped      = buf_mapped_callback,
    .buf_unmapped    = buf_unmapped_callback,
    .create_buf_file = create_buf_file_callback,
    .remove_buf_file = remove_buf_file_callback,
};

int relay_init(void){
	relay_rchan = relay_open("blockinfo", NULL, 1024*1024*1024, 1, &relay_callbacks, NULL);
	    if(NULL == relay_rchan){  
        printk("relay_open() failed.\n");
        return -1;
    }
	return 0;
}

void relay_exit(void)
{
    if(relay_rchan) {
        relay_close(relay_rchan);
        relay_rchan = NULL;
    }
}


//======================= relayfs ====================================

/*=======================netlink=======================================

int incmon_netlink_send(char* msg, int len){
	int rc = 0;
	int size;
	struct sk_buff *skb;
	struct nlmsghdr *nlh;

	size = NLMSG_SPACE(len);

	if(user_pid == 0 || nl_sk == NULL || msg == NULL){
		printk("incmon_netlink_send send fail\n");
		return -1;
	}

	skb = alloc_skb(size, GFP_ATOMIC);
	nlh = nlmsg_put(skb, 0, 0, 0, len, 0);
	memcpy(NLMSG_DATA(nlh), msg, len);
	NETLINK_CB(skb).pid = 0;

	rc = netlink_unicast(nl_sk, skb, user_pid, MSG_DONTWAIT);
	if(rc < 0){
		printk("incmon_netlink_send send fail\n");
		return -1;
	}
	return 0;
}


void incmon_netlink_recv(struct sk_buff* __skb){
	struct sk_buff *skb;
	struct nlmsghdr *nlh = NULL;

	skb = skb_get(__skb);
	if(skb->len >= sizeof(struct nlmsghdr)){
		nlh = (struct nlmsghdr*)skb->data;
		if(nlh->nlmsg_len >= sizeof(struct nlmsghdr) && (__skb->len >= nlh->nlmsg_len)){
			user_pid = nlh->nlmsg_pid;
			printk("incmon_netlink_recv: %s\n", (char*)NLMSG_DATA(nlh));
		}
	}
	kfree_skb(skb);
}

static int incmon_netlink_init(void){
	nl_sk = netlink_kernel_create(&init_net, NETLINK_SOCKNO, 0, incmon_netlink_recv, NULL, THIS_MODULE);
	if(nl_sk == NULL){
		printk("incmon: netlink init fail\n");
		return -1;
	}
	printk("incmon: netlink init ok\n");
	return 0;
}

static void incmon_netlink_exit(void){
	if(nl_sk != NULL)
		sock_release(nl_sk->sk_socket);
	printk("incmon: netlink exit ok\n");
}
//=======================netlink=======================================*/



static int __init incmon_init(void){
	int ret = -1;
	int i = 0;
	char* p = NULL;
	struct hd_struct ** hds_tbl;
	printk("=================== incmon_init ==================\n");

//	relay_init();

	bdev = incmon_get_bld_by_path(dname, FMODE_READ);
	if(!bdev)
		printk("open %s fail\n", dname);

	sdbm.major = bdev->bd_disk->major;
	sdbm.first_minor = bdev->bd_disk->first_minor;
	p = strstr(dname, bdev->bd_disk->disk_name);
	p += strlen(bdev->bd_disk->disk_name);
	sscanf(p, "%d", &sdbm.partno);
	strcpy(sdbm.disk_name, bdev->bd_disk->disk_name);
	hds_tbl = bdev->bd_disk->part_tbl->part;
	sdbm.sector_start = hds_tbl[sdbm.partno]->start_sect;
	sdbm.sector_end = hds_tbl[sdbm.partno]->start_sect + hds_tbl[sdbm.partno]->nr_sects ;
	for(i = 0; i < bdev->bd_disk->part_tbl->len; i++)
		printk("part[%d],disk.major: %d, first_minor: %d,  partno: %d,  start_sect: %lu, nr_sector: %lu\n", i, bdev->bd_disk->major, bdev->bd_disk->first_minor, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);
	
	get_blk_mrf(bdev);
	ret = set_blk_mrf(bdev, &sdbm.blk_org_mrf);
	if(ret == 0)
		printk("hook %s ok\n", dname);

printk("--------------------\n");
	printk("sdbm.major :%d\n", sdbm.major);
	printk("sdbm.first_minor: %d\n", sdbm.first_minor);
	printk("sdbm.partno: %d\n", sdbm.partno);
	printk("sdbm.disk_name: %s\n", sdbm.disk_name);
	printk("sdbm.sector_start: %lu\n", sdbm.sector_start);
	printk("sdbm.sector_end  : %lu\n", sdbm.sector_end);
	printk("sdbm.org_mrf: %p\n", sdbm.blk_org_mrf);
printk("--------------------\n");

	blkdev_put(bdev, FMODE_READ);
	bdev=NULL;
#if 1
	bdev = incmon_get_bld_by_path(dname1, FMODE_READ);
	if(!bdev)
		printk("open %s fail\n", dname1);

	sdcm.major = bdev->bd_disk->major;
	sdcm.first_minor = bdev->bd_disk->first_minor;
	p = strstr(dname1, bdev->bd_disk->disk_name);
	p += strlen(bdev->bd_disk->disk_name);
	sscanf(p, "%d", &sdcm.partno);
	strcpy(sdcm.disk_name, bdev->bd_disk->disk_name);
	hds_tbl = bdev->bd_disk->part_tbl->part;
	sdcm.sector_start = hds_tbl[sdcm.partno]->start_sect;
	sdcm.sector_end = hds_tbl[sdcm.partno]->start_sect + hds_tbl[sdcm.partno]->nr_sects ;
	for(i = 0; i < bdev->bd_disk->part_tbl->len; i++)
		printk("part[%d],disk.major: %d, first_minor: %d,  partno: %d,  start_sect: %lu, nr_sector: %lu\n", i, bdev->bd_disk->major, bdev->bd_disk->first_minor, hds_tbl[i]->partno, hds_tbl[i]->start_sect,  hds_tbl[i]->nr_sects);

	get_blk_mrf(bdev);
	ret = set_blk_mrf(bdev, &sdcm.blk_org_mrf);
	if(ret == 0)
		printk("hook %s ok\n", dname1);
printk("--------------------\n");
    printk("sdcm.major :%d\n", sdcm.major);
    printk("sdcm.first_minor: %d\n", sdcm.first_minor);
    printk("sdcm.partno: %d\n", sdcm.partno);
    printk("sdcm.disk_name: %s\n", sdcm.disk_name);
    printk("sdcm.sector_start: %lu\n", sdcm.sector_start);
    printk("sdcm.sector_end  : %lu\n", sdcm.sector_end);
    printk("sdcm.org_mrf: %p\n", sdcm.blk_org_mrf);
printk("--------------------\n");


	blkdev_put(bdev, FMODE_READ);
#endif
	return 0;
}

static void __exit incmon_exit(void){
    bdev = incmon_get_bld_by_path(dname, FMODE_READ);
	reset_blk_mrf(bdev, sdbm.blk_org_mrf);
	blkdev_put(bdev, FMODE_READ);

	bdev = incmon_get_bld_by_path(dname1, FMODE_READ);
	reset_blk_mrf(bdev, sdcm.blk_org_mrf);
	blkdev_put(bdev, FMODE_READ);
	

//	relay_exit();

	printk("=================== incmon_exit ==================\n");
}

module_init(incmon_init);
module_exit(incmon_exit);

MODULE_LICENSE("GPL");
