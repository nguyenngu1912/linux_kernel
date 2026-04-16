//GPIO PIN IN LINUX DRIVER (NOT DEVICE TREE)
//WARNING: THIS METHOD WILL WORK IN RASP PI, NOT SURE ABOUT OTHERS EMBEDDED SYSTEM OR x86 ARCHITECTURE
#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led;
static int my_init(void);
static void my_exit(void);

#define IO_LED 17

#define IO_OFFSET 512

static int __init my_init(void){
	int status;
	led = gpio_to_desc(IO_LED + IO_OFFSET);
	if(!led){
		printk("gpioCtrl - Error getting pin %d\n",IO_LED);
		return -ENODEV;
	}

	status = gpiod_direction_output(led, 0);
	if(status){
		printk("gpioCtrl - Error getting pin %d to output\n",IO_LED);
		return status;
	}
	
	printk("Begin module!!\n");
	gpiod_set_value(led,1);
	return 0;
}

static void __exit my_exit(void){
	gpiod_set_value(led,0);
	printk("Remove module\n==================\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ngu Cao Nguyen");
MODULE_DESCRIPTION("Example for using GPIO without device tree");
