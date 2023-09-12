#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/ioctl.h>

#define set_clear_VALUE _IOW(MY_MAGIC,'a',int32_t*)

int32_t value = 0;

/* Meta Information */
MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("gpio driver for setting a LED and reading a button");

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_gpio_driver"
#define DRIVER_CLASS "MyModuleClass"

static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	//int ret_val=0;
	//printk("entered in read.....");
	//ret_val=gpio_get_value(17);
	//printk("gpio read.....");
	printk(" Data read from gpio:: %d",gpio_get_value(4));
	return 0;
}

static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int ret_val=0;
	gpio_set_value(4, 1);
	ret_val++;
	printk("write operation done .....");
	return ret_val;
}

static int driver_open(struct inode *device_file, struct file *instance) {
	printk("open was called!\n");

	
	/* GPIO 4 init */
	if(gpio_request(4, "rpi-gpio-4")) {
		printk("Can not allocate GPIO 4\n");
		goto AddError;
	}

	/* Set GPIO 4 direction */
	if(gpio_direction_output(4, 0)) {
		printk("Can not set GPIO 4 to output!\n");
		goto Gpio4Error;
	}

	/* GPIO 17 init */
	if(gpio_request(17, "rpi-gpio-17")) {
		printk("Can not allocate GPIO 17\n");
		goto Gpio4Error;
	}

	/* Set GPIO 17 direction */
	if(gpio_direction_input(17)) {
		printk("Can not set GPIO 17 to input!\n");
		goto Gpio17Error;
	}

	return 0;
	
	Gpio17Error:
	gpio_free(17);
	Gpio4Error:
	gpio_free(4);
	AddError:
	device_destroy(my_class, my_device_nr);
	
	return -1;
	

}

static int driver_close(struct inode *device_file, struct file *instance) {
	printk("close was called!\n");

	gpio_set_value(4, 0);
	gpio_free(17);
	gpio_free(4);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Exit from Kernel\n");

	return 0;
}
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{	
	int raw;
	printk(KERN_INFO"Enter ioctl ");
	
	raw = copy_from_user(&value ,(int32_t*) arg, sizeof(value));
	if(raw>0)
	{
		printk(KERN_INFO"writing data failed\n");
		return raw;
	}
	gpio_set_value(4, value);
	printk(KERN_INFO "Value = %d\n", value);
	return 0;
 }

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.unlocked_ioctl = my_ioctl,
	.write = driver_write
};

static int __init ModuleInit(void) {
	printk("Enter in Kernel!\n");

	/* Allocate a device nr */
	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	//printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);
	printk(KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (my_device_nr),MINOR (my_device_nr));

	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created!\n");
		goto ClassError;
	}

	/* create device file */
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}

	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Regisering device to kernel */
	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}


	return 0;

AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

static void __exit ModuleExit(void) {

	gpio_set_value(4, 0);
	gpio_free(17);
	gpio_free(4);
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Exit from Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);


