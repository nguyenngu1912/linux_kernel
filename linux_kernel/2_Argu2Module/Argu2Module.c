//https://sysprog21.github.io/lkmpg/
// PASSING AN COMMAND LINE ARGUMENT TO MODULE

#include <linux/init.h>
#include <linux/kernel.h> // For ARRAY_SIZE() 

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include <linux/stat.h>	// used to make file permission constants 

MODULE_LICENSE("GPL");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
// declare a static char pointer variable named mystring
// initialized to point to the string literal "blah".
 
static int myintarray[2] = {420, 420};
static int arr_argc = 0;

//module_param(foo, int , 0000)
// * first parameter: para's name 
// * second parameter: data type
// * third parameter: is the permission bits

module_param(myshort, short, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");  // Add description

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");

module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long");

module_param(mystring, charp, 0000 );  
// charp type specifier for a char pointer
// 0000: File permission bits (octal) for the sysfs entry, means no permissions for anyone
// the parameter will not appear in /sys/module/<module>/parameters/
MODULE_PARM_DESC(mystring, "A character string");

module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int my_init(void);
static void my_exit(void);

static int __init my_init(void)
{
	int i;
	pr_info("Begin!!\n");
	pr_info("myshort is a short integer: %hd\n", myshort);
	pr_info("myint is an integer: %d\n", myint);  
	pr_info("mylong is a long integer: %ld\n", mylong);
	pr_info("mystring is a string: %s\n", mystring);
	
	for (i = 0; i < ARRAY_SIZE(myintarray); i++ )
	{
		pr_info("myintarray[%d] = %d\n",i,myintarray[i]);
	} 
	pr_info("got %d arguments for myintarray.\n",arr_argc);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Removed the module from kernel!!\n===============\n");
}

module_init(my_init);
module_exit(my_exit);
