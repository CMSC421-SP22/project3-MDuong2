#include "buffer_mon.c"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void *prothread(void *args){
	char printer[6];
	char num;
	char string[DATA_LENGTH];
	int counter = 0;
	for(int i = 0; i < 10; i++){
		sleep(((rand() % 10) + 1 )*.001);
		num = ((counter % 10) + '0');
		for(int j = 0; j < DATA_LENGTH; j++){
			string[j] = num;
			if(j < sizeof(printer)){
				printer[j] = num;
			}
		}
		if(enqueue_buffer_421(string) != -1){
			printf("::ENQUEUEING::");
			printf("%s\n", printer);
			printf("\n%d ", buffer->length);
			printf("nodes long\n");
			counter++;
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&filled);
		}
		else{
			i--;
			pthread_mutex_unlock(&mutex);
		}
	}
}
void *conthread(void *args){
	char temp[DATA_LENGTH];
	char printer[6];
	for(int i = 0; i < 10; i++){
		sleep(((rand() %  10) + 1) * .001);
		if(dequeue_buffer_421(temp) != -1){
			printf("::DEQUEUEING::");
			for(int j = 0; j < sizeof(printer); j++){
				printer[j] = temp[j];
			}
			printer[sizeof(printer)] = '\0';
			printf("%s\n", printer);
			printf("%d ", buffer->length);
			printf(" nodes long\n");
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&empty);
		}else{
			i--;
			pthread_mutex_unlock(&mutex);
		}
	}
}
int main(){
	printf("BEGINS HERE\n");
	init_buffer_421();
	pthread_t prod, con;
	pthread_create(&prod, NULL, prothread, NULL);
	sleep(2);
	pthread_create(&con, NULL, conthread, NULL);
	pthread_join(prod,NULL);
	pthread_join(con, NULL);
	delete_buffer_421();
}
