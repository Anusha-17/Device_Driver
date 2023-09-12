/*No exit exp code*/

#include<linux/module.h>
#include<linux/init.h>

static int  __init my_init(void)
{
        printk(KERN_INFO "Hello world\n");
        return 0;
}


module_init(my_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandan");
MODULE_DESCRIPTION("No exit  simple module");
