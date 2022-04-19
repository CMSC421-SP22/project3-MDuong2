#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>
#include <linux/string.h>
#include "buffer_sem.h"

static struct semaphore mutex;
static struct semaphore fill_count;
static struct semaphore empty_count;
struct bb_buffer_421 *buf_sem;

SYSCALL_DEFINE0(init_buffer_sem_421){
	if(buf_sem){
		return -1;
	}else{
		buf_sem = kmalloc(sizeof(struct bb_buffer_421), GFP_KERNEL);
		buf_sem->length = 0;
		buf_sem->read = NULL;
		buf_sem->write = NULL;
		sema_init(&fill_count, 0);
		sema_init(&mutex, 1);
		sema_init(&empty_count, 20);
		for(int i = 0; i < SIZE_OF_BUFFER; i++){
			struct bb_node_421 *prev;
			struct bb_node_421 *newNode = kmalloc(sizeof(struct bb_node_421), GFP_KERNEL);
			memset(newNode->data, 0,DATA_LENGTH);
			if(buf_sem->read != NULL){
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER -1){
					newNode->next = buf_sem->read;
				}
				prev = newNode;
			}else{
				buf_sem->read = newNode;
				buf_sem->write = newNode;
				prev = newNode;
			}
		}
	}
	return 0;
}
SYSCALL_DEFINE1(enqueue_buffer_sem_421, char*, data){
	if(!buf_sem){
		return -1;
	}else{
		down(&mutex);
		buf_sem->length += 1;
		memcpy(buf_sem->write->data, data, DATA_LENGTH);
		buf_sem->write = buf_sem->write->next;
		up(&fill_count);
		down(&empty_count);
		up(&mutex);
	}
	return 0;
}
SYSCALL_DEFINE1(dequeue_buffer_sem_421, char*, data){
	if(!buf_sem){
		return -1;
	}
	else{
		down(&mutex);
		buf_sem->length -= 1;
		memcpy(buf_sem->read->data, data, sizeof(buf_sem->read->data));
		memset(buf_sem->read->data, 0, sizeof(buf_sem->read->data));
		buf_sem->read = buf_sem->read->next;
		up(&empty_count);
		down(&fill_count);
		up(&mutex);
	}
	return 0;
}
SYSCALL_DEFINE0(delete_buffer_sem_421){
	if(!buf_sem){
		return -1;
	}else{
		int nodes = 1;
		while(SIZE_OF_BUFFER > nodes){
			struct bb_node_421 *temp = buf_sem->read;
			struct bb_node_421 *prev = temp;
			while(temp->next != buf_sem->read){
				prev = temp;
				temp = temp->next;
			}
			kfree(temp);
			temp = NULL;
			prev->next = buf_sem->read;
			nodes++;
		}
		kfree(buf_sem->read);
		buf_sem->read = NULL;
		buf_sem->write = NULL;
		buf_sem->length = 0;
		kfree(buf_sem);
		buf_sem = NULL;
	}
	return 0;
}
