#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static int major = 99; 
static int minor = 0;  

static dev_t devno;
static struct cdev cdev1;
struct class *hello_class;

static int hello_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_ALERT "hello are opened\n");
    return 0;
}

static ssize_t hello_write(struct file *filp, const char __user *buf, size_t size,	loff_t *ppos){
	char buffer[20] = {0};
	char* buff = NULL;
	int rc = -1;
	printk("size:%lu", size);
	if(size<20-1){
		rc = copy_from_user(buffer, buf,size);
		printk(KERN_ALERT "%s\n", buffer);
	}
	else
	{
		buff = (char*)kmalloc(size, GFP_ATOMIC);
		rc = copy_from_user(buff, buf,size);
		buff[size] = '\0';
		printk(KERN_ALERT "%lu,%s\n",size, buff);
		kfree(buff);
		buff = NULL;
	}
		
	printk(KERN_ALERT "hello are written\n");
	return 0;
}

static struct file_operations hello_ops = {
    .open = hello_open,
	.write = hello_write,
};

static int hello_init(void)
{
    int ret;
    printk(KERN_ALERT "hello_init\r\n");

    devno = MKDEV(major, minor);
    ret = register_chrdev_region(devno, 1, "hello");
    if (ret < 0)
    {
        printk(KERN_ERR "my register_chrdev_region fail \r\n");
        return ret;
    }
    printk(KERN_INFO "register_chrdev_region success\n");
  
    cdev_init(&cdev1, &hello_ops);
    ret = cdev_add(&cdev1, devno, 1);
    if (ret < 0)
    {
        printk(KERN_ERR "Uable to add dev\n");
        return ret;
    }
    printk(KERN_INFO "cdev_add success\n");

    hello_class = class_create(THIS_MODULE, "hello");
    device_create(hello_class, NULL, devno, NULL, "hello");
    printk(KERN_INFO "device created success\n");
    return 0;
}
static void hello_exit(void)
{
    cdev_del(&cdev1);
    unregister_chrdev_region(devno, 1);
    printk(KERN_ALERT "hell_exit\r\n");
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
