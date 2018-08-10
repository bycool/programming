#include "sync.h"

static int __init sync_init(void){
    int rc = -1;

    rc = relay_init();
    if(0 != rc) { printk("relay init fail\n"); return -1; }

    rc = sync_hook_init();
    if(0 != rc) { printk("syscall hook fail\n"); return -1; }

    printk("sync driver load ok\n");
    return 0;
}

static void __exit sync_exit(void){

    sync_unhook_exit();

    relay_exit();

    printk("sync driver unload ok\n");
}

module_init(sync_init);
module_exit(sync_exit);

MODULE_LICENSE("GPL");
