/*   
 * stop.c - Illustration of multi filed modules  
 */
 
  
#include <linux/kernel.h> /* We are doing kernel work */
#include <linux/module.h> /* Specifically, a module  */  


void my_exit(void);

void my_exit(void)  
{
 
    printk("Short is the life of a kernel module\n");  
}  

module_exit(my_exit);
MODULE_LICENSE("GPL");
