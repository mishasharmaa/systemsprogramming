#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE(“GPL”);
MODUE_AUTHOR(“Misha Sharma: 100826646”);
MODULE_DESCRIPTION(“100826646: This is Misha Sharma’s first Kernel module”);
MODULE_VERSION(“1.0);
Static int __init welcome_function(void)
{
printk(KERN_INFO “welcome to systems programming\n”);
Return 0;
}
static void __exit cleaning_function(void)
{
printk(KERN_INFO “Cleaning up the kernel module\n”);
}
module_intit(welcome_function);
module_exit(cleaning_function);
