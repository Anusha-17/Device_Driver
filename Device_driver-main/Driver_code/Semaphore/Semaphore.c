#include 	<linux/kernel.h>
#include	<linux/module.h>
#include	<linux/init.h>
#include 	<linux/slab.h>        /* kmalloc() */
#include	<linux/fs.h>
#include	<linux/mm.h>
#include	<linux/cdev.h>
#include	<linux/errno.h>
#include	<linux/types.h>
#include	<linux/interrupt.h>
#include	<linux/delay.h>
#include    <linux/errno.h>
#include    <linux/sched.h>
#include    <linux/semaphore.h>
#include	<linux/uaccess.h>
#include 	<linux/io.h>
#include 	<linux/version.h>

dev_t dev =0;


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johny");
MODULE_DESCRIPTION(" major and minor  driver");
MODULE_VERSION("1.0.0");

static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer =NULL;
#define MEM_SIZE        1024           //Memory Size

//static DEFINE_SEMAPHORE(mysema);  
static struct semaphore mysema;  
static int      __init my_driver_init(void);
static void     __exit my_driver_exit(void);
static int      my_open(struct inode *inode, struct file *file);
static int      my_release(struct inode *inode, struct file *file);
static ssize_t  my_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  my_write(struct file *filp, const char *buf, size_t len, loff_t * off);



static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = my_read,
    .write      = my_write,
    .open       = my_open,
    .release    = my_release,
};


static int my_open(struct inode *inode, struct file *file)
{
	
	int i;
	printk(KERN_INFO"Driver open  function called .....\n");
	
	//If the semaphore is successfully obtained, log will be printed for every 1s
	while(down_interruptible(&mysema)!=0);
	for(i=0;i<10;i++)
	{
		printk(KERN_INFO"semaphore test %d",i);
		ssleep(1);
	}
	//Release the semaphore. After each open node will get the  mysema again*/
	up(&mysema);  
	return 0;	
}
static int my_release(struct inode *inode, struct file *file)
{
	
	printk(KERN_INFO"Driver release function called ....\n");
	return 0;
}
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	int ret =0;
	//Copy the data from the kernel space to the user-space
    ret = copy_to_user(buf, kernel_buffer, MEM_SIZE);
	if(ret > 0)
	{
		printk(KERN_INFO"writing data to user-space failed\n");
	}
	printk(KERN_INFO"Driver read function called .....\n");
	return 0;
}
static ssize_t my_write(struct file *filp, const char __user *buf,size_t len,loff_t *off)
{
	int ret = 0;
	//Copy the data to kernel space from the user-space
	copy_from_user(kernel_buffer, buf, len);
	if(ret > 0)
	{
		printk(KERN_INFO"Copy the data to kernel space from the user-space\n");
	}
	printk(KERN_INFO"Driver write function called .... \n");
	return len;
} 
static int __init my_driver_init(void)
{
	//Create a semaphore mysema dynamically, and set the count to 1
	sema_init(&mysema, 1); 
	
	if((alloc_chrdev_region(&dev,0,1,"my_Sem_Char"))<0)
	{
		printk(KERN_INFO"cannot allocate major and minor number");
		return -1;
	}
	printk(KERN_INFO"Major =%d Minor = %d \n",MAJOR(dev),MINOR(dev));
	
	//creating cdev structure
	cdev_init(&my_cdev,&fops);
	
	//Adding charriver to system
	if((cdev_add(&my_cdev,dev,1)) <0)
	{
		printk(KERN_INFO"cannot add the device to the system \n");
		goto r_class;
	}

	if((dev_class = class_create(THIS_MODULE,"my_Sem_Char_class")) == NULL){
		printk(KERN_INFO"Cannot create the struct class for device");
		goto r_class;
	}
	if((device_create(dev_class,NULL,dev,NULL,"my_Sem_Char_driver"))==NULL) {
		printk(KERN_INFO" cannot create the device\n");
		goto r_device;
	}

	printk(KERN_INFO"character drivre with sem init sucess\n");

	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

static void __exit my_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "kernel driver removed  ... done \n");

}
module_init(my_driver_init);
module_exit(my_driver_exit);
