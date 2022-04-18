#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "buffer_mon.h"
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct ring_buffer_421 *buffer;
pthread_mutex_t mutex;
pthread_cond_t  filled;
pthread_cond_t empty;

long init_buffer_421(void){
	if(!buffer){
		buffer = malloc(sizeof(struct ring_buffer_421));
		buffer->read = NULL;
		buffer->write = NULL;
		buffer->length = 0;
		struct node_421 *prev;
		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init(&filled, NULL);
		pthread_cond_init(&empty, NULL);
		for(int i = 0; i < SIZE_OF_BUFFER; i++){
			struct node_421 *newNode = malloc(sizeof(struct node_421));
			memset(newNode->data, 0, DATA_LENGTH);
			if(buffer->read == NULL){
				buffer->read = newNode;
				buffer->write = newNode;
				prev = newNode;
			}else{
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER -1){
				newNode->next = buffer->read;
				}
				prev = newNode;
			}
		}
	}else{
		return -1;
	}
}

long enqueue_buffer_421(char *data){
	if(!buffer){
		return -1;
	}
	pthread_mutex_lock(&mutex);
	while(buffer->length >= SIZE_OF_BUFFER){
		pthread_cond_wait(&empty, &mutex);
	}
	buffer->length += 1;
	memcpy(buffer->write->data, data, DATA_LENGTH);
	buffer->write = buffer->write->next;
	return 0;
}

long dequeue_buffer_421(char *data){
	if(!buffer){
		return -1;
	}
	pthread_mutex_lock(&mutex);
	while(buffer->length <= 0){
		pthread_cond_wait(&filled, &mutex);
	}
	buffer->length -= 1;
	memcpy(data, buffer->read->data, sizeof(buffer->read->data));
	memset(buffer->read->data, 0, sizeof(buffer->read->data));
	buffer->read = buffer->read->next;
	return 0;
}

long delete_buffer_421(void){
	if(!buffer){
		return -1;
	}else{
		int nodes = 1;
		while(nodes < SIZE_OF_BUFFER){
			struct node_421 *prev = buffer->read;
			struct node_421 *temp = buffer->read;
			while(temp->next != buffer->read){
				prev = temp;
				temp = temp->next;
			}
			free(temp);
			temp = NULL;
			prev->next = buffer->read;
			nodes++;
		}
		free(buffer->read);
		buffer->read = NULL;
		buffer->write = NULL;
		buffer->length = 0;
		free(buffer);
		buffer = NULL;
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&filled);
		pthread_cond_destroy(&empty);
		//DESTROY MONITORS
		return 0;
	}
}

