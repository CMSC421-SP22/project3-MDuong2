#include "buffer_user_sem.c"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

long print_buffer_421(void){
	struct bb_node_421 *temp = buffer.read;
	int itr = 0;
	while(itr < SIZE_OF_BUFFER){
		printf("Node: %d\n", itr);
		printf("Data: %s\n", temp->data);
		temp = temp->next;
		itr++;
	}
}
void *prothread(void *args){
	char array;
	char string[DATA_LENGTH];
	char printer[6];
	int counter = 0;
	for(int i = 0; i < 1000; i++){
		sleep(((rand() % 10) + 1) * .001);
		array = ((counter % 10) + '0');
		for(int j = 0; j < DATA_LENGTH; j++){
			string[j] = array;
			if(j < sizeof(printer)){
				printer[j] = array;
			}
		}
		if(enqueue_buffer_421(string) != -1){
			printf("::ENQUEUEING:: ");
			for(int j = 0 ; j < sizeof(printer); j++){
				printf("%c", printer[j]);
			}
			printf("\n%d ", buffer.length);
			printf("nodes long\n");
			sem_post(&mutex);
			counter++;
		}else{
			i--;
			sem_post(&mutex);
		}
	}
}
void *conthread(void *args){
	char temp[DATA_LENGTH] = "\0";
	char printer[6];
	for(int i = 0; i < 1000; i++){
		sleep(((rand() % 10) + 1) * .001);
		if(dequeue_buffer_421(temp) != -1){
			printf("::DEQUEUEING:: ");
			for(int j = 0; j < sizeof(printer); j++){
				printer[j] = temp[j];
			}
			printer[sizeof(printer)] = '\0';
			printf("%s\n", printer);
			printf("%d ", buffer.length);
			printf("nodes long\n");
			sem_post(&mutex);
		}else{
			i--;
			sem_post(&mutex);
		}
	}
}
int main(){
	printf("start\n");
	init_buffer_421();
	pthread_t producer, consumer;
	pthread_create(&producer, NULL, prothread, NULL);
	sleep(2);
	pthread_create(&consumer, NULL, conthread, NULL);
/*	for(int i = 0; i < SIZE_OF_BUFFER; i++){
		enqueue_buffer_421("123");
		print_semaphores();
	}
	for(int i =0; i < SIZE_OF_BUFFER; i++){
		char temp[DATA_LENGTH];
		dequeue_buffer_421(temp);
		printf(temp);
		print_semaphores();
	}*/
	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);
	delete_buffer_421();
	printf("DONE\n");
}/*
	enqueue_buffer_421("a");
	char data[DATA_LENGTH];
	dequeue_buffer_421(data);
	print_semaphores();
	delete_buffer_421();
	printf("post delete\n");
	return 0;
}*/
