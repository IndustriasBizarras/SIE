/*
 *  Interrupt device driver demo
 *
 *  Author:     Andres Calderon
 *  Created:    September 16, 2005
 *  Copyright:  (C) 2005 emQbit Ltda
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <linux/init.h>
#include <linux/slab.h> /* kmalloc() */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/interrupt.h>  /* We want an interrupt */
#include <linux/irq.h>        /* We want an interrupt */
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <asm/uaccess.h>  
#include <asm/io.h>
#include <linux/gpio.h>
#include <asm/mach-jz4740/gpio.h>
#include <linux/input.h>
#include <linux/clk.h>
#include <linux/mmc/host.h>
#include <linux/io.h>
#include <linux/scatterlist.h>


#define FPGA_IRQ_PIN          JZ_GPIO_PORTC(15)
#define FPGA_BASE             0x15000000    //FPGA_BASE (FPGA) 0x14000000 - 0x17FFFFFF //
#define SUCCESS               0
#define DEVICE_NAME           "irq"    /* Dev name as it appears in /proc/devices   */
#define BUF_LEN               80       /* Max length of the message from the device */


  
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static int irq_enabled = 0;
static int is_device_open = 0; /* Is device open?  Used to prevent multiple access to device */
static int Major; 

void __iomem *ioaddress;
static unsigned int  interrupt_counter = 0;

static DECLARE_WAIT_QUEUE_HEAD(wq);


struct file_operations fops = {
  .owner  = THIS_MODULE,
  .read   = device_read,
  .write  = device_write,
  .open   = device_open,
  .release = device_release
};



static irqreturn_t irq_handler(int irq, void *dev_id)
{
  if(irq_enabled)
  {
    int a;
    a = inb(FPGA_BASE);
    printk(KERN_INFO "interrupt_counter=%d\n",a);
    copy_to_user()
    wake_up_interruptible(&wq);
  }
  
  return IRQ_HANDLED;
}


static int __init qem_init(void)
{
  int res, irq;
  printk(KERN_INFO "FPGA module is Up.\n");
  interrupt_counter = 0;
         
  Major = register_chrdev(0, DEVICE_NAME, &fops);         
  
  if (Major < 0) {
      printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  } 
  
  printk(KERN_ALERT  "I was assigned major number %d. To talk to\n", Major);
  printk(KERN_ALERT  "the driver, create a dev file with\n");
  printk(KERN_ALERT  "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
  
  
  /* Set up the FGPA irq line */ 
  irq = gpio_to_irq(FPGA_IRQ_PIN);
  
  res = request_irq(irq, irq_handler, IRQF_DISABLED | IRQF_TRIGGER_RISING, "FPGA - IRQ", NULL); // IRQF_TRIGGER_FALLING
       
  ioaddress = ioremap(FPGA_BASE, 0x4000);
       
  return 0;
}


static void __exit qem_exit(void)
{
//  int ret;
  /*Tho order for free_irq, iounmap & unregister is very important */
  free_irq(FPGA_IRQ_PIN, NULL);         
  iounmap(ioaddress);
  unregister_chrdev(Major, DEVICE_NAME);
  printk(KERN_INFO "FPGA driver is down...\n");
}


static int device_open(struct inode *inode, struct file *file)
{
  if (is_device_open)
    return -EBUSY;

  is_device_open = 1;

  try_module_get(THIS_MODULE);

  return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{ 
  is_device_open = 0;  

  module_put(THIS_MODULE);

  return 0;
}

static ssize_t device_read(struct file *filp, /* see include/linux/fs.h   */
         char *buffer,  /* buffer to fill with data */
         size_t count, /* length of the buffer     */
         loff_t *offset)
{ 
return 0;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t count, loff_t * off)
{
  return 0;
}

module_init(qem_init);
module_exit(qem_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andres Calderon <andresn@emqbit.com>");
MODULE_DESCRIPTION("FPGA' IRQ driver");
MODULE_VERSION("1:0.1");
