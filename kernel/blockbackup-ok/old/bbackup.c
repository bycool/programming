#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/version.h>

#include "bb.h"

int __init bbackup_init(void){
	printk("[bbackup start]\n");
	bbrelay_init();
	return 0;
}

void __exit bbackup_exit(void){
	bbdev_unhook_devs();
	cleanup_rulist();
	bbrelay_exit();
	printk("[bbackup exit]\n");
}

module_init(bbackup_init);
module_exit(bbackup_exit);

MODULE_LICENSE("GPL");
