/*
 *  Driver preliminar y de pruebas de teclado ps2 kbps2
 *
 *  Author: Ari Andrés Bejarano H.
 *
 */

#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO, printk() */
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/interrupt.h>  /* We want an interrupt */
#include <linux/irq.h>        /* We want an interrupt */
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  
#include <asm/io.h>            /*ioremap ioremap_nocache iounmap iowriteXX ioreadXX*/
#include <linux/gpio.h>
#include <asm/mach-jz4740/gpio.h>
#include<asm/system.h>         /*rmb*/

#define FPGA_IRQ_PIN          JZ_GPIO_PORTC(15)
#define FPGA_CS               JZ_GPIO_PORTB(26)
#define FPGA_BASE_BEGIN       0x15000000
#define FPGA_BASE_END         0x17FFFFFF
#define SUCCESS               0
#define DEVICE_NAME           "kbps2"    /* Dev name as it appears in /proc/devices   */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ari");
MODULE_DESCRIPTION("Keyboard ps2");
MODULE_VERSION("1.0");

/* Declaration of kbps2.c functions */
static irqreturn_t irq_handler(int irq, void *dev_id);
static int kbps2_open(struct inode *, struct file *);
static int kbps2_release(struct inode *, struct file *);
static ssize_t kbps2_read(struct file *, char *, size_t, loff_t *);
static ssize_t kbps2_write(struct file *, const char *, size_t, loff_t *);
static int __init kbps2_init(void);
static void __exit kbps2_exit(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations fops = {
  .owner  = THIS_MODULE,
  .read   = kbps2_read,
  .write  = kbps2_write,
  .open   = kbps2_open,
  .release = kbps2_release
};

/* Declaration of the init and exit functions */
module_init(kbps2_init);
module_exit(kbps2_exit);

/* Global variables of the driver */
static int irq_enabled = 0;
static int is_device_open = 0; /* Is device open?  Used to prevent multiple access to device */
static int Major=65; /* Major number */
static DECLARE_WAIT_QUEUE_HEAD(wq);
static void __iomem *ioaddress;
static unsigned int  interrupt_counter = 0;

static int __init kbps2_init(void)
{
  int res, irq, result;
  
  barrier();
  
  printk(KERN_INFO "FPGA module is Up.\n");
  interrupt_counter = 0;
  
  /* Registering device */
  result = register_chrdev(Major, DEVICE_NAME, &fops);
  if (result < 0) {
      printk("<1>memory: cannot obtain major number %d\n", Major);
    return result;
  }  
  
  /* Set up the FGPA irq line */ 
  irq = gpio_to_irq(FPGA_IRQ_PIN);
  res = request_irq(irq, irq_handler, IRQF_DISABLED | IRQF_TRIGGER_RISING, "FPGA - IRQ", NULL); // IRQF_TRIGGER_FALLING
  irq_enabled = 1;
  printk(KERN_INFO "FPGA irq_enabled...\n");
  
  /* Set GPIOB26 as part of External Memory Controller*/
  jz_gpio_set_function (FPGA_CS, JZ_GPIO_FUNC_NONE);
  /* Use ioremap to get a handle on our region */
  ioaddress = __ioremap(FPGA_BASE_BEGIN, FPGA_BASE_END - FPGA_BASE_BEGIN, _CACHE_UNCACHED);

  return 0;
}

static void __exit kbps2_exit(void)
{
//  int ret;
  /*Tho order for free_irq, iounmap & unregister is very important */
  free_irq(FPGA_IRQ_PIN, NULL);         
  __iounmap(ioaddress);
  unregister_chrdev(Major, DEVICE_NAME);
  printk(KERN_INFO "FPGA driver is down...\n");
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
  unsigned int red;
  if(irq_enabled)
  {
    interrupt_counter++;
    printk(KERN_INFO "interrupt_counter=%d\n",interrupt_counter);
    red=ioread32(ioaddress)& 0XFF;
    rmb();
    printk("%X \n", red);
    wake_up_interruptible(&wq);
  }
  
  return IRQ_HANDLED;
}

static int kbps2_open(struct inode *inode, struct file *file)
{
  if (is_device_open)
    return -EBUSY;

  is_device_open = 1;

  try_module_get(THIS_MODULE);

  return SUCCESS;
}

static int kbps2_release(struct inode *inode, struct file *file)
{ 
  is_device_open = 0;  

  module_put(THIS_MODULE);

  return 0;
}

static ssize_t kbps2_read(struct file *filp, char *buffer, size_t count, loff_t *offset)
{ 
  unsigned int red;
   
  printk(KERN_INFO "read______-_-\n");
  red=ioread32(ioaddress)& 0XFF;
  rmb();
  printk("%X\n", red);
  return 0;
}

static ssize_t kbps2_write(struct file *filp, const char *buff, size_t count, loff_t * off)
{

  printk(KERN_INFO "write______-_-\n");
  printk("%X\n", buff[0]);
  iowrite32(buff[0],ioaddress);
  wmb();
  
  return 1;
}
