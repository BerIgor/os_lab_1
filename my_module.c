/* my_module.c: Example char device module.
 *
 */
/* Kernel Programming */
#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kernel.h>  	
#include <linux/module.h>
#include <linux/fs.h>       		
#include <asm/uaccess.h>
#include <linux/errno.h>  

#include "my_module.h"

#define MY_DEVICE "my_device"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anonymous");

/* globals */
int my_major = 0; /* will hold the major # of my device driver */
my_list minor_list;


struct file_operations my_fops = {
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
    .ioctl = my_ioctl
};


int init_module(void)
{
    my_major = register_chrdev(my_major, MY_DEVICE, &my_fops);

    if (my_major < 0){
		printk(KERN_WARNING "can't get dynamic major\n");
		return my_major;
    }
	
	my_list=(my_list)kmalloc(sizeof(my_list));
	if(my_list==NULL){
		printk(KERN_WARNING "can't get dynamic allocation\n");
		return -ENOMEM;
	}
	my_list.my_alloc=(alloc_fun)create_element;
	my_list.my_free=(free_fun)destroy_element;
	my_list.head=NULL;
    return 0;
}


void cleanup_module(void)
{
    unregister_chrdev(my_major, MY_DEVICE);
	
	my_element element=my_list->head;
	my_element next;
	while(element!=NULL){
		next=element->next;
		my_list.free_fun(element);
		element=next;
	}
    return;
}


int my_open(struct inode *inode, struct file *filp)
{
	
	my_element new_element = find_element(filp->)
	
    if (filp->f_mode & FMODE_READ){
	
    }
    
    if (filp->f_mode & FMODE_WRITE){
        //
        // handle write opening
        //
    }

    return 0;
}


int my_release(struct inode *inode, struct file *filp)
{
    if (filp->f_mode & FMODE_READ)
    {
	//
	// handle read closing
	// 
    }
    
    if (filp->f_mode & FMODE_WRITE)
    {
        //
        // handle write closing
        //
    }

    return 0;
}


ssize_t my_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
    //
    // Do read operation.
    // Return number of bytes read.
    return 0; 
}


ssize_t my_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    //
    // Do write operation.
    // Return number of bytes written.
    return 0; 
}


int my_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
    case MY_OP1:
	//
	// handle OP 1.
	//
	break;

    default:
	return -ENOTTY;
    }

    return 0;
}
