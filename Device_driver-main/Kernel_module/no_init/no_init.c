/* No init exp code */

#include<linux/module.h>
#include<linux/init.h>

static void __exit my_exit(void)
{
        printk(KERN_INFO "no init exit function\n");
}


module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandan");
MODULE_DESCRIPTION("No init simple module");
                                           