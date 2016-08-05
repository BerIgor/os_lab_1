#ifndef _MY_MODULE_H_
#define _MY_MODULE_H_

#include <linux/ioctl.h>

#define MY_MAGIC 'r'
#define MY_OP1 _IOW(MY_MAGIC, 0, int)

typedef void* (*alloc_fun)();
typedef void (*free_fun)();

typedef struct my_element {
	struct my_element *next;
	unsigned int minor;
	void * data;
	int RP;	//file read permission 1 for yes
	int WP;	//file write permission -"-
} my_element;

typedef struct my_list {
	my_element *head;
	alloc_fun my_alloc;
	free_fun my_free;
} my_list;

//Data structure functions
void* create_element(){
	my_element element=kmalloc(sizeof(my_element));
	if(element==NULL){
		return ENOMEM;
	}
	element.RP=0;
	element.WP=0;
	return element;
}

void destroy_element(my_element *e){
	kfree(e);
}


//
// Function prototypes
//
int my_open(struct inode *, struct file *);

int my_release(struct inode *, struct file *);

ssize_t my_read(struct file *, char *, size_t, loff_t *);

ssize_t my_write(struct file *, const char *, size_t, loff_t *);

int my_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

#endif
