// https://sysprog21.github.io/lkmpg/ => follow this tutorial
// a difference approach with hello world linux kernel
// * NOTE: The old init_module() and cleanup_module() have been deprecated for x86 systems with indirect
// branch tracking (IBT) enabled starting from commit 4fab2d76 in kernel 6.15

#include <linux/module.h>  
#include <linux/printk.h> /* Needed for pr_info() */
#include <linux/init.h> 

static int my_init(void);
static void my_exit(void);
  
static int __init my_init(void)  
{  
    pr_info("Hello world 1.\n");  

 
    /* A nonzero return means init_module failed; module can't be loaded. */
 
    return 0;  
}  
  
static void __exit my_exit(void)  
{  
    pr_info("Goodbye world 1.\n");  
}

module_init(my_init);
module_exit(my_exit); 
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ngu Cao Nguyen");
MODULE_DESCRIPTION("Simple hello world");
