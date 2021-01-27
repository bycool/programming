#include <linux/string.h>
#include <linux/types.h>
#include <linux/version.h>
#include <asm/unistd.h>
#include <linux/module.h>
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
#include <asm-generic/atomic-long.h>

#include "bb.h"

struct bbnode {
    int ruleno;
    int major;
    int first_minor;
    int partno;
    char disk_name[DISK_NAME_LEN];
    unsigned long sector_s;
    unsigned long sector_e;
    struct bbnode* next;
};


atomic_t rule_state = ATOMIC_INIT(0);  //0:NULL rules, 1: rule6 online, 2: rule9 online
atomic_t rule6_used_cnt = ATOMIC_INIT(0);
atomic_t rule9_used_cnt = ATOMIC_INIT(0);
static struct bbnode rulist6 = {0,0,0,0,"0",0,0,NULL};
static struct bbnode rulist9 = {0,0,0,0,"0",0,0,NULL};;

//find: 1, find null: 0
static int find_rule_from_rulist(struct bbnode* head, int ruleno, int major, int first_minor, int partno, char* disk_name){
	int ret = 0;
	struct bbnode* tmp = NULL;

	tmp = head;
	while(tmp){
		if( (ruleno==tmp->ruleno) && (partno==tmp->partno) && !(strcmp(disk_name, tmp->disk_name)))
			ret = 1;
		tmp = tmp->next;
	}

	return ret;
}

// append: 0, append fail: 1
int append_rule_to_rulist(int ruleno, int major, int first_minor, int partno, char* disk_name, unsigned long sector_s, unsigned long sector_e){
	int ret = 0;
	struct bbnode* head = NULL;
	struct bbnode* new = NULL;
	struct bbnode* tmp = NULL;

	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 ) {  //cannot insert online rule
		head = &rulist6;
	} else if( atomic_read(&rule_state)== 1 ) {
		head = &rulist9;
	}

	ret = find_rule_from_rulist(head, ruleno, major, first_minor, partno, disk_name);

	if(ret)
		return ret;

	new = (struct bbnode*)kmalloc(sizeof(struct bbnode), GFP_ATOMIC);
	if(!new){
		ret = 1;
		printk("kmalloc bbnode fail\n");
		return ret;
	}

	new->ruleno = ruleno;
	new->major = major;
	new->first_minor = first_minor;
	new->partno = partno;
	strcpy(new->disk_name, disk_name);
	new->sector_s = sector_s;
	new->sector_e = sector_e;
	new->next = NULL;

	tmp = head;
	while(tmp->next) {
		tmp = tmp->next;
	}

	tmp->next = new;

	return ret;
}



static void cleanup_bblist(struct bbnode* b){
	struct bbnode *tmp = NULL;
	struct bbnode *dtmp = NULL;

	tmp = b;
	while(tmp){
		dtmp = tmp;
		tmp = tmp->next;
#if 0
		printk("------------------------------------------\n");
		printk("ruleno        : %d\n", dtmp->ruleno);
		printk("major         : %d\n", dtmp->major);
		printk("first_minor   : %d\n", dtmp->first_minor);
		printk("partno        : %d\n", dtmp->partno);
		printk("diskname:     : %s\n", dtmp->disk_name);
		printk("sector_s      : %lu\n", dtmp->sector_s);
		printk("sector_e      : %lu\n", dtmp->sector_e);
		printk("------------------------------------------\n");
#endif
		kfree(dtmp);
	}
}

void cleanup_rulist(){
	atomic_set(&rule_state, 0);
	cleanup_bblist(rulist6.next);
	cleanup_bblist(rulist9.next);
}

int rulists_set_finish(){
	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 ) {  // NULL rule || rulist9 online	
		atomic_set(&rule_state, 1);    //change online rule to  rulist6
		while( atomic_read(&rule9_used_cnt)!=0 )   // wait to clean rulist9
			msleep(5);
		cleanup_bblist(rulist9.next);
		rulist9.next = NULL;
		display_rulist(rulist6.next);
	}else if( atomic_read(&rule_state)== 1 ){
		atomic_set(&rule_state, 2);
		while( atomic_read(&rule6_used_cnt)!=0 )
			msleep(5);
		cleanup_bblist(rulist6.next);
		rulist6.next = NULL;
		display_rulist(rulist9.next);
	}
	return 0;
}

int bbdev_unhook_devs(){
	struct bbnode* head = NULL;
	struct bbnode* tmp = NULL;
	char devpath[32];
	int ret ;

    if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 ) {  //get online rule
        head = &rulist9;
    } else if( atomic_read(&rule_state)== 1 ) {
        head = &rulist6;
    }

	tmp = head->next;
	while(tmp){
		sprintf(devpath, "/dev/%s%d", tmp->disk_name, tmp->partno);
		printk("rmmod devpath: %s\n", devpath);
		ret = bbdev_unhook_mrf(devpath);
		if(ret!=0){
			printk("rmmod devs fail\n");
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}


void display_rulist(struct bbnode* rule){
	struct bbnode* tmp = rule;

	while(tmp){
		printk("+++++++++++++++++++++++++++++++++++++++++\n");
		printk("    ruleno        : %d\n", tmp->ruleno);
//		printk("    major         : %d\n", tmp->major);
//		printk("    first_minor   : %d\n", tmp->first_minor);
		printk("    diskname:     : %s\n", tmp->disk_name);
		printk("    partno        : %d\n", tmp->partno);
//		printk("    sector_s      : %lu\n", tmp->sector_s);
//		printk("    sector_e      : %lu\n", tmp->sector_e);
		printk("+++++++++++++++++++++++++++++++++++++++++\n");
		tmp = tmp->next;
	}
}

int bbfilter(char* devname, unsigned long sector_s, char* rulenos){
	int cnt = 0;
	char * p = NULL;
	struct bbnode* tmp = NULL;
//	struct bbnode* ptmp = NULL;
	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 ){
		tmp = rulist9.next;
//		atomic_add(1, &rule6_used_cnt);
	}else if( atomic_read(&rule_state)==1 ){
		tmp = rulist6.next;
//		atomic_add(1, &rule9_used_cnt);
	}
//	printk("devname: %s, sector: %lu\n", devname, sector_s);

	p = rulenos;
	for(; tmp!=NULL; tmp=tmp->next){
//		printk("%s::%s\n", tmp->disk_name, devname);
		if(!strcmp(tmp->disk_name,devname)){
			if(tmp->sector_s <= sector_s && sector_s <= tmp->sector_e){
				cnt++;
				p += sprintf(p, ".%d", tmp->ruleno);
			}
		}
	}
	p += sprintf(p, "\n");
	return cnt;
}

