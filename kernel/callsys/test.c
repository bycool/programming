#include <linux/autoconf.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_AUTHOR("wangzhangjun");
MODULE_DESCRIPTION("slab test module");

static struct kmem_cache  *test_cachep = NULL;
int n = 0;
struct slab_test
{
    int val;
};
void fun_ctor(struct slab_test *object , struct kmem_cache  *cachep , unsigned long flags )
{
    printk(KERN_INFO "ctor fuction ::%d...\n", n);
    object->val = 1;
	n++;
}

static int __init slab_init(void)
{
    struct slab_test *object = NULL;//slab的一个对象
	printk(KERN_INFO "slab_init\n");
    test_cachep = kmem_cache_create("test_cachep",sizeof(struct slab_test)*3,0,SLAB_HWCACHE_ALIGN,fun_ctor);
    if(NULL == test_cachep) 
                return  -ENOMEM ;
	printk(KERN_INFO "Cache name is %s\n",kmem_cache_name(test_cachep));//获取高速缓存的名称
	printk(KERN_INFO "Cache object size  is %d\n",kmem_cache_size(test_cachep));//获取高速缓存的大小
 	object = kmem_cache_alloc(test_cachep,GFP_KERNEL);//从高速缓存中分配一个对象
    if(object)
    {
        printk(KERN_INFO "alloc one val = %d\n",object->val);
        kmem_cache_free( test_cachep, object );//归还对象到高速缓存
		//这句话的意思是虽然对象归还到了高速缓存中，但是高速缓存中的值没有做修改
		//只是修改了一些它的状态。
		printk(KERN_INFO "alloc three val = %d\n",object->val);
            object = NULL;
        }else
            return -ENOMEM;
	return 0;
}

static void  __exit slab_clean(void)
{
	printk(KERN_INFO "slab_clean\n");
	if(test_cachep)
                kmem_cache_destroy(test_cachep);//调用这个函数时test_cachep所指向的缓存中所有的slab都要为空

}

module_init(slab_init);
module_exit(slab_clean);
MODULE_LICENSE("GPL");
