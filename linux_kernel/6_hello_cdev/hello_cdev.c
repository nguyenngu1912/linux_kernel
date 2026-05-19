#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>    //file system

//every major device number has 256 (0-255) minor device numbers
static int my_init(void);
static void my_exit(void);

static int major;
static ssize_t my_read (struct file *f, char __user *u, size_t l, loff_t *o)
{
	printk("hello cdev - Read is called\n");
	return 0;
}

static struct file_operations fops =  {
	.read = my_read
};

static int __init my_init(void)
{
	major = register_chrdev(0,"hello_cdev",&fops );   	 // create a character device and link device number
	if (major < 0){
		printk("hello cdev - Error registering chrdev\n");
		return major;
	}
	printk("hello cdev - Major Device Number: %d\n",major);
	return 0;
}
static void __exit my_exit(void)
{
	printk("hello cdev is about to exit!!\n");
	unregister_chrdev(major,"hello_cdev"); // delete character device and free device number
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ngu Nguyen");
MODULE_DESCRIPTION("A sample driver for registering a character device");
