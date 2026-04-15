#include <linux/module.h> /* Needed by all modules */  
#include <linux/printk.h> /* Needed for pr_info() */
#include <linux/init.h> 

int my_init(void);
void my_exit(void);
  
int my_init(void)  
{  
    pr_info("Hello world 1.\n");  

 
    /* A nonzero return means init_module failed; module can't be loaded. */
 
    return 0;  
}  
  
void my_exit(void)  
{  
    pr_info("Goodbye world 1.\n");  
}

module_init(my_init);
module_exit(my_exit); 
 
MODULE_LICENSE("GPL");
