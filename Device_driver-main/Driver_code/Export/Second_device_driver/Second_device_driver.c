#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_LICENSE("GPL v2");
MODULE_LICENSE("Dual BSD/GPL");

MODULE_AUTHOR("johny");
MODULE_DESCRIPTION("A sample driver");
MODULE_VERSION("1:0.0");

extern int my_count;
void my_func(void);
static int __init hello_world_init(void) /* Constructor */
{
	printk(KERN_INFO"hello this is my second");
	my_func();
    return 0;
}
module_init(hello_world_init);

void __exit hello_world_exit(void)
{
 printk(KERN_INFO"Exiting my second programming");
}
module_exit(hello_world_exit);

