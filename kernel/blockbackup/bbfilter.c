#include <stdio.h>
#include <string.h>

#define DISK_NAME_LEN 32

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
static struct bbnode* rulist6 = NULL;
static struct bbnode* rulist9 = NULL;

//find: 1, find null: 0
static int find_rule_from_rulist(int ruleno, int major, int first_minor, int partno, char* disk_name){
	int ret = 0;
	struct bbnode* head = NULL;
	struct bbnode* tmp = NULL;

	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 )
		head = rulist6;
	else if( atomic_read(&rule_state)== 1 )
		head = rulist9;

	tmp = head;
	while(tmp){
		if( (ruleno==tmp->ruleno) && (major==tmp->major) && (first_minor==tmp->first_minor) && !(strcmp(disk_name, tmp->disk_name)))
			ret = 1;
	}

	return ret;
}

// append: 0, append fail: 1
static int append_rule_to_rulist(int ruleno, int major, int first_minor, int partno, char* disk_name, unsigned long sector_s, unsigned long sector_e){
	int ret = 0;
	struct bbnode* head = NULL;
	struct bbnode* new = NULL;
	struct bbnode* tmp = NULL;

	if( atomic_read(&rule_state)==2 || atomic_read(&rule_state)==0 )  //cannot insert online rule
		head = rulist6;
	else if( atomic_read(&rule_state)== 1 )
		head = rulist9;

	ret = find_rule_from_rulist(ruleno, major, first_minor, partno, disk_name);

	if(ret)
		return ret;

	new = (struct bbnode*)kmalloc(sizeof(struct bbnode), GFP_ATOMIC);
	if(!new){
		ret = 1;
		printk("kmalloc bbnode fail\n");
		return ret;
	}

	new->ruleno = ruleno;
	new->first_minor = first_minor;
	new->partno = partno;
	strcpy(new->disk_name, disk_name);
	new->sector_s = sector_s;
	new->sector_e = sector_e;
	new->next = NULL;

	tmp = head;
	while(tmp->next)
		tmp = tmp->next;

	tmp->next = new;

	return ret;
}




