#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
 

#define mem_size        1024           //Memory Size


#define IRQ_NO 1
//Interrupt handler for IRQ 11. 
static irqreturn_t irq_handler(int irq,void *dev_id) {
  printk(KERN_INFO "Shared IRQ: Interrupt Occurred");
  return IRQ_HANDLED;
}
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev char_cdev;
uint8_t *kernel_buffer;

/*
** Function Prototypes
*/
static int      __init hello_driver_init(void);
static void     __exit hello_driver_exit(void);
static int      hello_open(struct inode *inode, struct file *file);
static int      hello_release(struct inode *inode, struct file *file);
static ssize_t  hello_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  hello_write(struct file *filp, const char *buf, size_t len, loff_t * off);
static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/*
** File Operations structure
*/
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = hello_read,
        .write          = hello_write,
        .open           = hello_open,
	.unlocked_ioctl = etx_ioctl,
        .release        = hello_release,
};
 
/*
** This function will be called when we write IOCTL on the Device file
*/
static long etx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
         switch(cmd) {
                case WR_VALUE:
                        if( copy_from_user(kernel_buffer,(int32_t*) arg, sizeof(kernel_buffer)) )//copy_from_user(kernel_buffer, buf, len)
                        {
                                pr_err("Data Write : Err!\n");
                        }
                        pr_info("Value = %s\n",kernel_buffer);
                        break;
                case RD_VALUE:
                        if( copy_to_user((int32_t*) arg,kernel_buffer, sizeof(kernel_buffer)) )
                        {
                                pr_err("Data Read : Err!\n");
                        }
                        break;
                default:
                        pr_info("Default\n");
                        break;
        }
        return 0;
}

/*
** This function will be called when we open the Device file
*/
static int hello_open(struct inode *inode, struct file *file)
{
        /*Creating Physical memory*/
        if((kernel_buffer = kmalloc(mem_size , GFP_KERNEL)) == 0){
            pr_info("Cannot allocate memory in kernel\n");
            return -1;
        }
        pr_info("Device File Opened...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/
static int hello_release(struct inode *inode, struct file *file)
{
        kfree(kernel_buffer);
        pr_info("Device File Closed...!!!\n");
        return 0;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t hello_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        //Copy the data from the kernel space to the user-space
	char buffer[100]="Hi userspace !!!!!\n";
        if( copy_to_user(buf,buffer,len) )
        {
                pr_err("Data Read : Err!\n");
        }
	pr_info("Data copied to userspace succefully!!!!!\n");
        return len;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t hello_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        //Copy the data to kernel space from the user-space
        if( copy_from_user(kernel_buffer, buf, len) )
        {
                pr_err("Data Write : Err!\n");
        }
        pr_info("Data from userspace :%s\n",kernel_buffer);
        return len;
}

/*
** Module Init function
*/
static int __init hello_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "char_Dev")) <0){
                pr_info("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&char_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&char_cdev,dev,1)) < 0){
            pr_info("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"char_class")) == NULL){
            pr_info("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"char_device")) == NULL){
            pr_info("Cannot create the Device 1\n");
            goto r_device;
        }
	if (request_irq(IRQ_NO, irq_handler, IRQF_SHARED, "char_device", (void *)(irq_handler))) {
            printk(KERN_INFO "my_device: cannot register IRQ ");
                    goto irq;
        }
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 irq:
        free_irq(IRQ_NO,(void *)(irq_handler));
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*
** Module exit function
*/
static void __exit hello_driver_exit(void)
{
	 free_irq(IRQ_NO,(void *)(irq_handler));
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&char_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}
 
module_init(hello_driver_init);
module_exit(hello_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("pallavi sonekar");
MODULE_DESCRIPTION("Simple Linux device driver ");
