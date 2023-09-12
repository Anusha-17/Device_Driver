#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>


#define IRQ_NO 1
int dev_id = 12;

static void tasklet_handler(unsigned long data);

DECLARE_TASKLET(my_tasklet,tasklet_handler,0);

/*dynamic

struct tasklet_struct my_tasklet;
tasklet_init(&my_tasklet,tasklet_handler,0);


*/

static void tasklet_handler(unsigned long data)
{

	printk(KERN_INFO"tasklet handler called\n");
	retrun 0;

}


static irqreturn_t intr_handler(int irq, void *dev_id)
{
    
    printk (KERN_INFO "Interrupt occured\n");
    
    tasklet_schedule(&my_tasklet);
    
    return IRQ_HANDLED;            
}

static int __init init_module (void)
{
    if (request_irq(IRQ_NO, intr_handler, IRQF_SHARED, "my_interrupt", &dev_id))
    {
    	printk( KERN_INFO "	registering interrupt handler failed \n");
    	return -1;
    }
    
    printk (KERN_INFO "module inserted successfully\n");
    return 0;
}

static void __exit exit_module (void)
{
    
    tasklet_kill(&my_tasklet);
    free_irq (IRQ_NO, &dev_id);
    printk (KERN_INFO "Successfully unloading \n");
}

module_init (init_module);
module_exit (exit_module);

MODULE_AUTHOR ("suresh");
MODULE_DESCRIPTION ("sample interrupt handler on tasklets");
MODULE_LICENSE ("GPL");
