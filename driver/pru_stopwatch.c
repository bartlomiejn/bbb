#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Bartlomiej Nowak");
MODULE_DESCRIPTION("Driver for AM335x PRU");
MODULE_VERSION("0.1");

static char *name = "test";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "Test parameter");

static int __init pru_sw_init(void)
{
    printk(KERN_INFO "%s: init\n", name);
    return 0;
}

static void __exit pru_sw_exit(void)
{
    printk(KERN_INFO "%s: exit\n", name);
}

module_init(pru_sw_init);
module_exit(pru_sw_exit);
