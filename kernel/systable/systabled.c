#include <linux/init.h>
#include <asm/unistd.h>
#include <linux/sched.h>
#include <linux/module.h>  
#include <linux/kernel.h>

#include "nsysfunc.h"


//将systable内的function替换为nsysfunction
#define NSYS(function) \
do{ \
	old_##function = (sys_##function##_t)sys_call_table[__NR_##function]; \
	sys_call_table[__NR_##function] = nsys_##function; \
}while(0);

//systable内的function换回old_function
#define OSYS(function)	\
do{ \
	if(old_##function != NULL) \
		sys_call_table[__NR_##function] = old_##function; \
}while(0);


static void **sys_call_table=NULL;


//声明旧系统函数变量,用于保存原系统调用函数地址。
sys_write_t old_write = NULL;
sys_mkdir_t old_mkdir = NULL;
sys_rmdir_t old_rmdir = NULL;


static void *getsystable(void){

    unsigned long tble;
    __asm__(
        "mov %0, r8"
        :"=r" (tble)
        :
    );

    return (void *)tble;
}

static int  __init systabled_init(void){
	printk("systabled init\n");

	sys_call_table = (void**)getsystable();
	if(sys_call_table == NULL)
		return -1;


	NSYS(write);
	NSYS(mkdir);
	NSYS(rmdir);


	return 0;
}

static void __exit systabled_exit(void){
	printk("systabled exit\n");


	OSYS(write);
	OSYS(mkdir);
	OSYS(rmdir);

}

module_init(systabled_init);
module_exit(systabled_exit);

MODULE_LICENSE("GPL");
