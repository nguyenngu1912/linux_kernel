/*   
 * start.c - Illustration of multi filed modules  
 */

#include <linux/kernel.h> /* We are doing kernel work */
#include <linux/module.h> /* Specifically, a module */

int my_init(void);

int my_init(void)  
{
 
    printk("Hello, world - this is the kernel speaking\n");  
    return 0;  
}
 
module_init(my_init); 
MODULE_LICENSE("GPL");
