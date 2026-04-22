Control LED through GPIO with Linux Kernel (NOT WITH DEVICE TREE !!) 
-
Hardware
-
1. Raspberry Pi 4
2. 330 Ohm resistor
3. LED
4. Jumping wires

Updates and installations
-
1. Update: sudo apt-get update && sudo apt-get upgrade -y
2. install: sudo apt install raspberrypi-kernel-headers
3. Reboot : sudo reboot

Diagram
-
<img width="1156" height="688" alt="image" src="https://github.com/user-attachments/assets/1a4d5ff0-c007-41dd-8106-a874bb159f65" />


System
-
1. Host: Linux os (ubuntu 22.0.4)
2. Rasp: Debian Trixie (No desktop, newest in Imager)

How to do it?
-
Step 1: Connect ssh to rasp pi.  
Step 2: Create folder to store the source code with mkdir and touch command.  
Step 3: Detect gpio with driver: gpiodetect and go to /sys/class/gpio/ to calculate offset  
<img width="402" height="43" alt="image" src="https://github.com/user-attachments/assets/4b58af95-c117-4b19-859d-35d32f3e0d49" />
This is the result when you type gpiodetect  
<img width="402" height="42" alt="image" src="https://github.com/user-attachments/assets/be269529-5021-4904-9712-c13eac7f9664" />  
This is the result when you cd to the path and ls, focus on the label start with gpiochipxx, as we can see the gpiodetect about will give us 2 different labels, if you want to check what is the relation between them use cat gpiochipxx/label to compare.  
<img width="444" height="42" alt="image" src="https://github.com/user-attachments/assets/0b7741c8-0f54-4931-beda-829707514bd0" />  
Now we will see there are 2 name with the same label pinctrl-bcm2711, remember this to calculate IO_OFFSET later.  
Note: The existence of both gpiochip0 and gpiochip512 is due to a change in the Linux kernel's GPIO numbering scheme introduced in kernel 6.6  
Step 4: Create 2 files: Make file and file code c (eg. led.c, ...).  
Step 5:  
- Contents in Make file:  
obj-m += gpioCtrl.o  
all:  
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules  
clean:  
        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

- Code in file .c  
/GPIO PIN IN LINUX DRIVER (NOT DEVICE TREE)    
//WARNING: THIS METHOD WILL WORK IN RASP PI, NOT SURE ABOUT OTHERS EMBEDDED SYS>  
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

Step 6: compile code with make command and fix the issue if it appears.  
Step 7: Open another terminal check messages of kernel with sudo dmesg -W, sudo insmod file.ko to insert module and sudo rmmod file.ko to remove module


