#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/semaphore.h>
#include <linux/string.h>
struct semaphore mutex;
struct semaphore fill_count;
struct semaphore empty_count;
struct bb_buffer_421 buffer;

SYSCALL_DEFINE0(init_buffer_sem_421){
	if(!buffer){
		return -1;
	}else{
		buffer = kmalloc(sizeof(struct bb_buffer_421), GFP_KERNEL);
		buffer->length = 0;
		buffer->read = NULL;
		buffer->write = NULL;
		//ASSIGN SEMAPHORES

		for(int i = 0; i < SIZE_OF_BUFFER; i++){
			struct bb_node_421 *prev;
			sturct bb_node_421 *newNode = kalloc(sizeof(struct bb_node_421), GFP_KERNEL);
			memset(newNode->data, 0,DATA_LENGTH);
			if(buffer->read != null){
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER -1){
					newNode->next = buffer->read;
				}
				prev = newNode;
			}else{
				buffer->read = newNode;
				buffer->write = newNode;
				prev = newNode;
			}
		}
		return 0;
	}
}
SYSCALL_DEFINE1(enqueue_buffer_sem_421, char*, data){
	if(!buffer){
		return -1;
	}else{
		//LOCK MUTEX
		buffer->length += 1;
		memcpy(buffer->write->data, data, sizeof(data));
		buffer->write = buffer->write->next;
		//POST FILL
		//WAIT EMPTY
		return 0;
	}
}
SYSCALL_DEFINE1(dequeue_buffer_sem_421, char*, data){
	if(!buffer){
		return -1;
	}
	else{
		//LOCK MUTEX
		buffer->length -= 1;
		memcpy(buffer->read->data, data, sizeof(buffer->read->data));
		memset(buffer->read->data, 0, sizeof(buffer->read->data));
		buffer->read = buffer->read->next;
		//POST EMPTY
		//WAIT FILL
		return 0;
	}
}
SYSCALL_DEFINE0(delete_buffer_sem_421){
	if(!buffer){
		return -1;
	}else{
		int nodes = 1;
		while(SIZE_OF_BUFFER > nodes){
			struct bb_node_421 *temp = buffer->read;
			struct bb_node_421 *prev = temp;
			while(temp->next != buffer->read){
				prev = temp;
				temp = temp->next;
			}
			kfree(temp);
			temp = NULL;
			prev->next = buffer->read;
			nodes++;
		}
		kfree(buffer->read);
		buffer->read = NULL;
		buffer->write = NULL;
		buffer->length = 0;
		kfree(buffer);
		buffer = NULL;
		//FREE SEMAPHORES
		return 0;
	]
}
