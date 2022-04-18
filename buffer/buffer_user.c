#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "buffer.h"

long init_buffer_421(void);
long insert_buffer_421(int i);
long print_buffer_421(void);
long delete_buffer_421(void);

struct ring_buffer_421 *buff;

long init_buffer_421(void){
	if(!buff){ //The buffer has been not created
		buff = malloc(sizeof(struct ring_buffer_421));
		buff->length = 0;
		buff->read = NULL;
		buff->write = NULL;
		struct node_421 *prev;
		for(int i = 0; i < SIZE_OF_BUFFER; i++){
			struct node_421 *newNode = malloc(sizeof(struct node_421));
			newNode->data = 0;
			if(buff->read == NULL){
				buff->write = newNode;
				buff->read = newNode;
				prev = newNode;
			}
			else{
				prev->next = newNode;
				if(i == SIZE_OF_BUFFER -1){
					newNode->next = buff->read;
				}
				prev = newNode;
			}
		}
		return 0;
	}
	else{
		return -1;
	}

}

long insert_buffer_421(int i){
	if(!buff){ //The buffer does not exist
		return -1;
	}
	if(buff->length == SIZE_OF_BUFFER){ //The buffer has no free spaces left
		printf("Buffer is full \n");
		return -1;
	}
	else{ //The buffer has free spaces]
		buff->length += 1;
		buff->write->data = i;
		buff->write = buff->write->next;
		return 0;
	}
	return 0;
}

long print_buffer_421(){
	if(!buff){ //The buffer does not exist
		return -1;
	}
	else{
		struct node_421 *temp = buff->read;
		int itr = 0;
		while(itr < SIZE_OF_BUFFER){ //While the next node exists and it has not looped through the ring buffer
			printf("Node: ");
			printf("%d\n", itr);
			printf("Data: ");
			printf("%d\n", temp->data);
			temp = temp->next;
			itr++;
		}
		return 0;
	}
}

long delete_buffer_421(){
	if(!buff){ // If the ring buffer does not exist
		return -1;
	}else{
		struct node_421 *prev = buff->read;
		int numNodes = 1;
		while(SIZE_OF_BUFFER > numNodes){
			struct node_421 *temp = buff->read;
			while(temp->next != buff->read){
				prev = temp;
				temp = temp->next;
			}
			free(temp);
			temp = NULL;
			prev->next = buff->read;
			numNodes++;
		}
		free(buff->read);
		buff->write = NULL;
		buff->read = NULL;
		buff->length = 0;
		free(buff);
		buff = NULL;
	}
	return 0;
}


