#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/wait.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/device.h>

#include<linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,15,0)
#include<linux/sched/signal.h>
#endif

int delay=HZ;

static struct task_struct * thread_wait;

static int thread_func(void *wait)
{
	
	unsigned long j1,j2;
	
	while(!kthread_should_stop())
	{
	j1=jiffies;
	set_current_state(TASK_INTERRUPTIBLE); //ensures that the scheduler wont run the currerent process agian untill the timeout places it back in TASK_RUNNABLE state,it wakes up prematurely if it receive signal

	schedule_timeout(delay);  //this functin internally create timer,call puts your task to sleep until specified time elapsed   
	j2=jiffies;
	
	printk("jiffies starts =%lu \t and jiffies ends=%lu \n",j1,j2);
	if(signal_pending(current))
		break;
	}
	printk(KERN_INFO"thread is stopped ..\n");
	thread_wait=NULL;
	do_exit(0);

}

static int __init my_init(void)
{
	printk(KERN_INFO"creating a thread...\n");
	thread_wait = kthread_run(thread_func,NULL,"mythread");
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO"Removing the module..\n");

	if(thread_wait!=NULL)
	{
		kthread_stop(thread_wait);
		printk(KERN_INFO"stopping the threa\n");
	}
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manikanta");
MODULE_DESCRIPTION("schedule  sample code");




















