#include "buffer.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>
struct ring_buffer_421 *buffer;

SYSCALL_DEFINE0(init_buffer_421){
	if(!buffer){
		buffer = kmalloc(sizeof(struct ring_buffer_421), GFP_KERNEL);
		buffer->length = 0;
		buffer->read = NULL;
		buffer->read = NULL;
		struct node_421 *prev = NULL;
		int i = 0;
		while(i < SIZE_OF_BUFFER){
			struct node_421 *newNode = kmalloc(sizeof(struct node_421), GFP_KERNEL);
			newNode->data = 0;
			if(buffer->read == NULL){
				buffer->write = newNode;
				buffer->read = newNode;
				prev = newNode;
			}else{
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER - 1){
					newNode->next = buffer->read;
				}
				prev = newNode;
			}
			i++;
		}
		return 0;
	}else{
		printk("Buffer already exists(init)\n");
		return -1;
	}
}

SYSCALL_DEFINE1(insert_buffer_421, int, i){
	if(!buffer){
		printk("Buffer doesn't exist(insert)\n");
		return -1;
	}
	if(buffer->length == SIZE_OF_BUFFER){
		printk("Buffer is full\n");
		return -1;
	}
	else{
		buffer->length += 1;
		buffer->write->data = i;
		buffer->write = buffer->write->next;
		return 0;
	}
}

SYSCALL_DEFINE0(print_buffer_421){
	if(!buffer){
		printk("No buffer(print)\n");
		return -1;
	}else{
		struct node_421 *temp = buffer->read;
		int itr = 0;
		while(itr < SIZE_OF_BUFFER){
			printk("Node: ");
			printk("%d", itr);
			printk("Data: ");
			printk("%d", temp->data);
			temp = temp->next;
			itr++;
		}
		return 0;
	}
}

SYSCALL_DEFINE0(delete_buffer_421){
	if(!buffer){
		printk("buffer doesn't exist(delete)\n");
		return -1;
	}else{
		struct node_421 *prev = buffer->read;
		int numNodes = 1;
		while(SIZE_OF_BUFFER > numNodes){
			struct node_421 *temp = buffer->read;
			while(temp->next != buffer->read){
				prev = temp;
				temp = temp->next;
			}
			kfree(temp);
			temp = NULL;
			prev->next = buffer->read;
			numNodes++;
		}
		kfree(buffer->read);
		buffer->read = NULL;
		buffer->write = NULL;
		buffer->length = 0;
		kfree(buffer);
		buffer = NULL;
	}
	return 0;
}
