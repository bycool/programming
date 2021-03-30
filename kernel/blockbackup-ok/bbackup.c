#include "bb.h"

int __init bbackup_init(void){
	printk("[bbackup start]\n");
	bbrelay_init();
	return 0;
}

void __exit bbackup_exit(void){
	cleanup_rulist();
	bbrelay_exit();
	printk("[bbackup exit]\n");
}

module_init(bbackup_init);
module_exit(bbackup_exit);

MODULE_LICENSE("GPL");
