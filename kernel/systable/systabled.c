#include <linux/init.h>
#include <linux/module.h>  
#include <linux/kernel.h>

#include <linux/sched.h>
#include <asm/unistd.h>


static unsigned int org_cr0 = 0;

static unsigned long **sys_call_table=NULL;
typedef asmlinkage int (*type_org_mkdir)(const char*, int);
type_org_mkdir org_mkdir;

struct _idtr {
    unsigned short limit;
    unsigned long base; //in 64bit mode, base address is 8 bytes
} idtr;

typedef struct _idt{
    u16 offset_low;
    u16 segment;
    unsigned ist : 3, zero0 : 5, type : 5, dpl :2, p : 1;
    u16 offset_middle;
    u32 offset_high;
    u32 zero1;
}idt;

static unsigned long clear_and_return_origcr0(void){
	unsigned long cr0 = 0;
	unsigned ret;

	asm volatile ("mov %%cr0,%0;clts" : "=r"(cr0));
	ret = cr0;
	cr0 &= 0xfffffffffffeffff;

	__asm__ __volatile__
	(
		"movq %%rax,%%cr0"
		::"a"(cr0)
	);
	return ret;
}


static void setback_cr0(unsigned long val){
	__asm__ __volatile__
	(
		"movq %%rax, %%cr0"
		::"a"(val)
	);
}

static void *memmem(const void *haystack, size_t haystack_len,
            const void *needle, size_t needle_len)
{
    const char *begin;
    const char *const last_possible
        = (const char *) haystack + haystack_len - needle_len;

    /* The first occurrence of the empty string is deemed to occur at
 *        the beginning of the string. 
 *             */
    if (needle_len == 0)
        return (void *) haystack;

    /* Sanity check, otherwise the loop might search through the whole
 *        memory. 
 *             */
    if (__builtin_expect(haystack_len < needle_len, 0))
        return NULL;

    for (begin = (const char *) haystack; begin <= last_possible; ++begin)
    {
        if (begin[0] == ((const char *) needle)[0]
            && !memcmp(begin + 1, needle + 1, needle_len - 1))
        {
            return (void *) begin;
        }
    }

    return NULL;
}


static void *getsystable(void){
    unsigned long syscall_long, retval;
    char sc_asm[150];

    rdmsrl(MSR_LSTAR, syscall_long);

    memcpy(sc_asm, (char*)syscall_long, 150);

    retval = (unsigned long)memmem(sc_asm, 150, "\xff\x14\xc5", 3);
    if ( retval != 0 )
    {
        retval = (unsigned long)(*(unsigned long*)(retval+3));
    }
    else
    {
        printk("long mode : memmem found nothing, returning NULL:( \n");
        retval = 0;
    }

    /* we must do it,otherwise the high 32-bit of retval would be wrong! */
    retval |= 0xffffffff00000000;

    return (void *)retval;
}

asmlinkage int hacked_mkdir(const char * pathname, int mode)  
{  
	printk("PID %d called sys_mkdir !\n",current->pid);  
	return org_mkdir(pathname,mode);  
}  

static int  __init systabled_init(void){
	printk("systabled init\n");

	sys_call_table      = (void**)getsystable();
	if(sys_call_table == NULL)
		return -1;

	org_cr0 = clear_and_return_origcr0();

	org_mkdir      =(type_org_mkdir)sys_call_table[__NR_mkdir];  
	sys_call_table[__NR_mkdir]=(long)hacked_mkdir;

	setback_cr0(org_cr0);

	printk("systabled initend\n");

	return 0;
}

static void __exit systabled_exit(void){
	printk("systabled exit\n");

	org_cr0 = clear_and_return_origcr0();

	sys_call_table[__NR_mkdir]=(unsigned long)org_mkdir; 

	setback_cr0(org_cr0);

	printk("systabled exit end\n");
}

module_init(systabled_init);
module_exit(systabled_exit);

MODULE_LICENSE("GPL");
