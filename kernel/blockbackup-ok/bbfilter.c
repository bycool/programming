#include "bb.h"

atomic_t rule_state = ATOMIC_INIT(0) ; // 0: non-rule, 1: rule6 online, 2: rule9 online
atomic_t rule6_used_cnt = ATOMIC_INIT(0) ;
atomic_t rule9_used_cnt = ATOMIC_INIT(0) ;

static struct bbnode rulist6 = {0,0,0,0,"0",0,0,NULL} ;
static struct bbnode rulist9 = {0,0,0,0,"0",0,0,NULL} ;

static int find_rule_from_rulist(struct bbnode* head, int ruleno, int major, 
									int first_minor, int partno, char* disk_name) {
	int ret = 0 ;
	struct bbnode* tmp ;

	tmp = head ;
	while(tmp) {
		if((ruleno==tmp->ruleno) && (partno==tmp->partno) && !(strcmp(disk_name, tmp->disk_name)))
			ret = 1 ;
		tmp = tmp->next ;
	}
	return ret ;
}

int append_rule_to_rulist(int ruleno, int major, int first_minor, int partno,
								char* disk_name, unsigned long sector_s, unsigned long sector_e){
	int ret = 0;
	struct bbnode* head = NULL;
	struct bbnode* new = NULL;
	struct bbnode* tmp = NULL;

	if(atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0)
		head = &rulist6 ;
	else if(atomic_read(&rule_state)== 1)
		head = &rulist9 ;

	ret = find_rule_from_rulist(head, ruleno, major, first_minor, partno, disk_name) ;

	if(ret)
		return ret ;

	new = (struct bbnode*)kmalloc(sizeof(struct bbnode), GFP_ATOMIC) ;
	if(!new) {
		ret = 1 ;
		printk("kmalloc bbnode fail\n") ;
		return ret ;
	}

	new->ruleno = ruleno ;
	new->major = major ;
	new->first_minor = first_minor ;
	new->partno = partno ;
	strcpy(new->disk_name, disk_name) ;
	new->sector_s = sector_s ;
	new->sector_e = sector_e ;
	new->next = NULL ;

	tmp = head ;
	while(tmp->next)
		tmp = tmp->next ;

	tmp->next = new ;

	return ret ;
}

static void rulist_enable(struct bbnode* b, int on) {
	char devpath[32] ;
	struct bbnode* tmp ;

	tmp = b ;
	while(tmp) {
		if(tmp->partno)
			sprintf(devpath, "/dev/%s%d", tmp->disk_name, tmp->partno) ;
		else
			sprintf(devpath, "/dev/%s", tmp->disk_name) ;

		printk("rulist_%s : %s\n", on==1 ? "enable":"disable", devpath) ;

		if(on)
			bbdev_setblk_mrf_bypath(devpath);
		else
			bbdev_resetblk_mrf_bypath(devpath) ;

		tmp = tmp->next ;
	}
}

static void cleanup_bb_rulist(struct bbnode* b) {  // clean up from rulist6.next rulist9.next
	struct bbnode* tmp ;
	struct bbnode* dtmp ;

	tmp = b;
	while(tmp) {
		dtmp = tmp ;
		tmp = tmp->next ;
#if 0
		printk("------------------------------------------\n");
		printk("ruleno        : %d\n", dtmp->ruleno);
		printk("major         : %d\n", dtmp->major);
		printk("first_minor   : %d\n", dtmp->first_minor);
		printk("partno        : %d\n", dtmp->partno);
		printk("diskname:     : %s\n", dtmp->disk_name);
		printk("sector_s      : %lu\n", dtmp->sector_s);
		printk("sector_e      : %lu\n", dtmp->sector_e);
#endif
		kfree(dtmp) ;
	}
//	printk("------------------------------------------\n");
}

void display_rulist(struct bbnode* rule) {
	struct bbnode* tmp = rule ;
	while(tmp) {
		printk("+++++++++++++++++++++++++++++++++++++++++\n");
		printk("    ruleno        : %d\n", tmp->ruleno);
//		printk("    major         : %d\n", tmp->major);
//		printk("    first_minor   : %d\n", tmp->first_minor);
		printk("    diskname:     : %s\n", tmp->disk_name);
		printk("    partno        : %d\n", tmp->partno);
		printk("    sector_s      : %lu\n", tmp->sector_s);
		printk("    sector_e      : %lu\n", tmp->sector_e);
		tmp = tmp->next ;
	}
	printk("+++++++++++++++++++++++++++++++++++++++++\n");
}

void cleanup_rulist() {
	atomic_set(&rule_state, 0) ;
	rulist_enable(rulist6.next, 0) ;
	cleanup_bb_rulist(rulist6.next) ;
	rulist_enable(rulist9.next, 0) ;
	cleanup_bb_rulist(rulist9.next) ;
	printk("[cleanup_rulist]\n");
}

int rulists_set_finish() {
	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 ) { // NULL rule || rulist9 online
		atomic_set(&rule_state, 1);    //change online rule to  rulist6
		while( atomic_read(&rule9_used_cnt)!=0 )  // wait to clean rulist9
			msleep(5);
		rulist_enable(rulist9.next, 0);
		cleanup_bb_rulist(rulist9.next);
		rulist9.next = NULL;
		rulist_enable(rulist6.next, 1);
		display_rulist(rulist6.next);
	}else if(atomic_read(&rule_state)== 1) {
		atomic_set(&rule_state, 2);
		while( atomic_read(&rule6_used_cnt)!=0 )
			msleep(5);
		rulist_enable(rulist6.next, 0);
		cleanup_bb_rulist(rulist6.next);
		rulist6.next = NULL;
		rulist_enable(rulist9.next, 1);
		display_rulist(rulist9.next);
	}
	return 0;
}

int bbfilter(char* devname, unsigned long sector_s, char* rulenos) {
	int cnt = 0 ;
	char* p = NULL ;
	struct bbnode* tmp = NULL ;

	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 )
		tmp = rulist9.next ;
	else if( atomic_read(&rule_state)==1 )
		tmp = rulist6.next ;

	p = rulenos ;
	for(; tmp!=NULL; tmp=tmp->next){
		if(!strcmp(tmp->disk_name,devname)){
			if(tmp->sector_s <= sector_s && sector_s <= tmp->sector_e){
				cnt++ ;
				p += sprintf(p, ".%d", tmp->ruleno) ;
			}
		}
	}
	p += sprintf(p, "\n") ;
	return cnt ;
}
