#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("May Robertson:100751769, Misha Sharma:100826646");
MODULE_DESCRIPTION("100751769: This is May Robertson’s & Misha Sharma's first Kernel
module");
MODULE_VERSION("1.0");
static int __init my_init(void) {
printk(KERN_INFO "This is the second Systems Programming Lab\n");
return 0;
}
static void __exit my_exit(void) {
printk(KERN_INFO "Cleaning up the Kernel Module\n");
}
module_init(my_init);
module_exit(my_exit);
