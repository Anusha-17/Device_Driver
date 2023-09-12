#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

//gpio 2 = LED
//gpio 4 = Push button
//gpio 17 = Read signal

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A gpio interrupt for operate LED using pushbutton");

unsigned int irq_number;

static irq_handler_t gpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) 
{
	printk("Interrupt triggered\n");
	gpio_set_value(2, 1);
		
	return (irq_handler_t) IRQ_HANDLED;
	//return 0; 
}

static int __init ModuleInit(void)
{

	if(!gpio_is_valid(2))
		return -1;

	if(!gpio_is_valid(4))
		return -1;

	if(!gpio_is_valid(17))
		return -1;
	
	/* GPIO 2 init for LED*/
	if(gpio_request(2, "gpio-2")) {
		printk("Can not allocate GPIO 2\n");
		goto Gpio2Error;
	}

	/* Set GPIO 2 direction */
	if(gpio_direction_output(2, 0)) {
		printk("Can not set GPIO 2 to output!\n");
		goto Gpio2Error;
	}	

	/* GPIO 4 init for Button*/
	if(gpio_request(4, "gpio-4")) {
		printk("Can not allocate GPIO 4\n");
		goto Gpio4Error;
	}

	/* Set GPIO 4 direction */
	if(gpio_direction_output(4, 0)) {
		printk("Can not set GPIO 4 to output!\n");
		goto Gpio4Error;
	}

	/* GPIO 17 init for Read signal*/
	if(gpio_request(17, "gpio-17")) {
		printk("Can not allocate GPIO 17\n");
		goto Gpio4Error;
	}

	/* Set GPIO 17 direction */
	if(gpio_direction_input(17)) {
		printk("Can not set GPIO 17 to input!\n");
		goto Gpio17Error;
	}
	printk("All requested GPIO allocated\n");	
	

	gpio_set_value(2, 1);// LED ON
	gpio_set_value(4, 1);// Button ON
	msleep(2000);

	gpio_set_value(2, 0);// LED OFF


	/* Setup the interrupt */
	irq_number = gpio_to_irq(17);

	if(request_irq(irq_number, (irq_handler_t) gpio_irq_handler, IRQF_TRIGGER_RISING, "my_gpio_irq", NULL) != 0){
		printk("Error!\nCan not request interrupt nr.: %d\n", irq_number);
		gpio_free(17);
		return -1;
	}

	printk("Done!\n");
	printk("GPIO 17 is mapped to IRQ Nr.: %d\n", irq_number);

	return 0;
	
	Gpio17Error:
	gpio_free(17);
	Gpio4Error:
	gpio_free(4);
	Gpio2Error:
	gpio_free(2);

	return -1;
}


static void __exit ModuleExit(void) {
	printk("gpio_irq: Unloading module... ");
	gpio_set_value(2, 0);
	gpio_set_value(4, 0);
	gpio_free(17);
	gpio_free(4);
	gpio_free(2);
	free_irq(irq_number, NULL);

}

module_init(ModuleInit);
module_exit(ModuleExit);


