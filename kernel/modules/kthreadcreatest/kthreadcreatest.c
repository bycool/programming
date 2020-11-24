#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/sched.h>

static struct task_struct* thd_printsth = NULL;
static struct task_struct* thd_state = NULL;

static int printsth(void* data){
	int cnt = 15;
	while(cnt > 0 &&! kthread_should_stop()){
		printk("kct: %d\n", cnt);
		cnt--;
		msleep(1000);
	}
	return 0;
}

static int state_print(void* data){
	
	while(!kthread_should_stop()){
		if(thd_printsth->state == TASK_DEAD){
			printk("TASK_DEAD\n");
			break;
		}
		msleep(10);
	}
	return 0;
}

static int __init kct_init(void){
	printk("kct_init\n");

	thd_printsth = kthread_create(printsth, NULL, "kct");
	if (!IS_ERR(thd_printsth))
		wake_up_process(thd_printsth);

//	thd_state = kthread_create(state_print, NULL, "state");
//	if(!IS_ERR(thd_state))
//		wake_up_process(thd_state);

	return 0;
}

static void __exit kct_exit(void){
	if(thd_printsth->state != TASK_DEAD)
		kthread_stop(thd_printsth);
//	kthread_stop(thd_state);
/*
	printk("on_rq: %u\n", thd_printsth->se.on_rq);
	printk("state: %d\n", thd_printsth->state);
	if(thd_printsth->state == 0){
		printk("thd_printsth is RUNNING\n");
	}
*/
	printk("kct_exit\n");
}

module_init(kct_init);
module_exit(kct_exit);

MODULE_LICENSE("GPL");
