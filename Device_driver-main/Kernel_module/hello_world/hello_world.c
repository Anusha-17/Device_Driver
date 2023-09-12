/* hello world char driver*/

#include<linux/init.h>
#include<linux/module.h>

static int my_init(void)
{
        pr_info("Hello world\n");
        return 0;
}

static void my_exit(void)
{
        pr_info("Goodbye world\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chandan");
MODULE_DESCRIPTION("simple hello world lkm");
