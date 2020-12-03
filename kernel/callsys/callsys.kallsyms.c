#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/version.h>
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
#include <linux/unistd.h>

#if 0
static unsigned long find_symbol_callback(char* syml, const char* name, struct module *mod, unsigned long addr){
	if(syml && name && !strcmp(syml, name)){
		return addr;
}
	ret = kallsyms_on_each_symbol((void *)find_symbol_callback, "sys_call_table");
#endif

unsigned long addr = 0;

int kallsymcall(void *data , const char *namebuff, struct module *mu,unsigned long address) 
{ 
	if(!strcmp((char*)data, namebuff)){
		addr = address;
    	printk("name=%s address=%p\n",namebuff,(void*)address); 
    //	printk("name=%s address=%lu\n",namebuff,(void*)address); 
	}
    	return 0; 
} 


static int __init callsys_init(void){
	int ret = -1;
	ret = kallsyms_on_each_symbol(kallsymcall, "sys_call_table");	
	if(addr != 0)
		printk("get ok\n");
	printk("callsys_init\n");
	return 0;
}

static void __exit callsys_exit(void){
	printk("callsys_exit\n");
}

module_init(callsys_init);
module_exit(callsys_exit);

MODULE_LICENSE("GPL");

