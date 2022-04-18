#include "buffer_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

long init_buffer_421(void){
	if(buffer.read || buffer.write){
		return -1;
	}else{
		//buffer = malloc(sizeof(struct bb_buffer_421));
		buffer.length = 0;
		buffer.read = NULL;
		buffer.write = NULL;
		sem_init(&mutex, 0,1);
		sem_init(&fill_count, 0, 0);
		sem_init(&empty_count, 0, SIZE_OF_BUFFER);
		for(int i = 0; i < SIZE_OF_BUFFER; i++){
			struct bb_node_421 *prev;
			struct bb_node_421 *newNode = malloc(sizeof(struct bb_node_421));
			memset(newNode->data, 0, DATA_LENGTH);
			if(buffer.read == NULL){
				buffer.read = newNode;
				buffer.write = newNode;
				prev = newNode;
			}else{
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER - 1){
					newNode->next = buffer.read;
				}
				prev = newNode;
			}
		}
		return 0;
	}
}

long enqueue_buffer_421(char *data){
	if(!buffer.read){
		return -1;
	}
	if(buffer.length == SIZE_OF_BUFFER){
		return -1;
	}
	sem_wait(&mutex);
	buffer.length += 1;
	memcpy(buffer.write->data, data, DATA_LENGTH);
	buffer.write = buffer.write->next;
	sem_post(&fill_count);
	sem_wait(&empty_count);
	//USE SEMAPHORE TO DECREASE EMPTY AND INCREMENT FILLED
	//LIBERATE MUTEX
	return 0;
}


long dequeue_buffer_421(char *data){
	if(!buffer.read){
		return -1;
	}
	if(buffer.length == 0){
		return -1;
	}
	sem_wait(&mutex);
	buffer.length -= 1;
	memcpy(data, buffer.read->data, sizeof(buffer.read->data)); //36 ERRORS in 5 contexts
	memset(buffer.read->data, 0, sizeof(buffer.read->data));
	buffer.read = buffer.read->next;
	sem_post(&empty_count);
	sem_wait(&fill_count);
	return 0;
}

long delete_buffer_421(void){
	if(!buffer.read){
		return -1;
	}else{
		int numNodes = 1;
		while(SIZE_OF_BUFFER > numNodes){
			struct bb_node_421 *temp = buffer.read;
			struct bb_node_421 *prev;
			while(temp->next != buffer.read){
				prev = temp;
				temp = temp->next;
			}
			free(temp);
			temp = NULL;
			prev->next = buffer.read;
			numNodes++;
		}
		free(buffer.read);
		buffer.read = NULL;
		buffer.write = NULL;
		buffer.length = 0;
		sem_destroy(&mutex);
		sem_destroy(&fill_count);
		sem_destroy(&empty_count);
	}
	return 0;
}

void print_semaphores(void){
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
