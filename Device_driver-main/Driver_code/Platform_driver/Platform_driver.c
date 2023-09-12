#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>        /* kmalloc() */
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/version.h>
#include <linux/platform_device.h>

static int      my_open(struct inode *inode, struct file *file);
static int      my_release(struct inode *inode, struct file *file);
static ssize_t  my_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  my_write(struct file *filp, const char *buf, size_t len, loff_t * off);

dev_t dev =0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer =NULL;
#define MEM_SIZE        1024           //Memory Size

static insigned int gpio_number = 0;

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
	
	if((kernel_buffer = kmalloc(MEM_SIZE,GFP_KERNEL))==0)
	{
		printk(KERN_INFO "Cannot allocate memory in kernel\n");
		return -1;
	}
	printk(KERN_INFO"Driver open  function called .....\n");
	return 0;	
}
static int my_release(struct inode *inode, struct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_INFO"Driver release function called ....\n");
	return 0;
}
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	int ret =0;
	unsigned char temp =  gpio_get_value(gpio_number);
	//Copy the data from the kernel space to the user-space
    ret = copy_to_user(buf, &temp, 1);
	if(ret > 0)
	{
		printk(KERN_INFO"reading data to user-space \n");
	}
	printk(KERN_INFO"Driver read function called .....\n");
	return 0;
}
static ssize_t my_write(struct file *filp, const char __user *buf,size_t len,loff_t *off)
{
	int ret = 0;
	char temp;
	//Copy the data to kernel space from the user-space
	ret = copy_from_user(&temp, buf, len);
	if(ret > 0)
	{
		printk(KERN_INFO"Copy the data to kernel space from the user-space\n");
	}
	printk(KERN_INFO"Driver write function called .... \n");
	switch(temp)
	{
		case '0':
			gpio_set_value(gpio_number,0)
			break;
		case '1':
			gpio_set_value(gpio_number,0)
			break;
		default:
			printk(KERN_INFO"invalid operation");
			break;
	return len;
} 
static int my_platform_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	printk(KERN_INFO"In probe function call");
	
	of_property_read_u32(np,"led_number",&gpio_number);
	
	if((alloc_chrdev_region(&dev,0,1,"my_Char"))<0)
	{
		printk(KERN_INFO"cannot allocate major and minor number");
		return -1;
	}
	printk(KERN_INFO"Major =%d Minor = %d \n",MAJOR(dev),MINOR(dev));
	
	//creating cdev structure
	cdev_init(&my_cdev,&fops);
	
	//Adding char driver to system
	if((cdev_add(&my_cdev,dev,1)) <0)
	{
		printk(KERN_INFO"cannot add the device to the system \n");
		goto r_class;
	}

	if((dev_class = class_create(THIS_MODULE,"my_Char_class")) == NULL){
		printk(KERN_INFO"Cannot create the struct class for device");
		goto r_class;
	}
	if((device_create(dev_class,NULL,dev,NULL,"my_Char_driver"))==NULL) {
		printk(KERN_INFO" cannot create the device\n");
		goto r_device;
	}

	printk(KERN_INFO"character drivre init sucess\n");

	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}
static const struct of_device_id gpio_led_dt[] = {
	{ .compatible = "my_platform_dt_name",},
		{}
};

static struct platform_driver my_platform_driver = {
	.driver = {
		.name	= "my_platform_device_name",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(my_platform_device_dt),
	},
	.probe		= my_platform_probe,
	.remove		= my_platform_remove,
	.suspend	= my_platform_suspend,
	.resume		= my_platform_resume,
};

static int __init my_platform_init(void)
{
	printk(KERN_INFO "My platform driver start");
	return platform_driver_register(&my_platform_driver);
}

module_init(my_platform_init);

static void __exit my_platform_exit(void)
{
	printk(KERN_INFO "My platform driver exit");
	platform_driver_unregister(&my_platform_driver);
}
module_exit(my_platform_exit);





/*
Chnages in device tree  
arch/arm/boot/dts/

Open some DTS file related to board 
example am335x-boneblack.dts 
my-leds {
	compatible = "my_platform_dt_name";
	led_number = <0x38>;
};
make dtbs

*/