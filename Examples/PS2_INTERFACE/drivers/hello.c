/* Necessary includes for drivers */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */

MODULE_LICENSE("GPL");

static int hello_init(void) {
  printk("Hello world!. init\n");
  return 0;
}

static void hello_exit(void) {
  printk("Bye, cruel world. exit\n");
}

module_init(hello_init);
module_exit(hello_exit)