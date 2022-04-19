#include <stdio.h>
#include <stdlib.h>
#include "buffer_sem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>

#define __NR_init_buffer_sem_421 446
long init_buffer_sem_syscall(void){
	return syscall(__NR_init_buffer_sem_421);
}
#define __NR_enqueue_buffer_sem_421 447
long enqueue_buffer_sem_syscall(char *data){
	return syscall(__NR_enqueue_buffer_sem_421, data);
}
#define __NR_dequeue_buffer_sem_421 448
long dequeue_buffer_sem_syscall(char *data){
	return syscall(__NR_dequeue_buffer_sem_421, data);
}
#define __NR_delete_buffer_sem_421 449
long delete_buffer_sem_syscall(void){
	return syscall(__NR_delete_buffer_sem_421);
}
void * prothread(void *args){
	char num;
	char string[DATA_LENGTH];
	char printer[6];
	int counter = 0;
	for(int i = 0; i < 1000; i++){
		sleep(((rand() % 10) +1) * .001);
		num = ((counter % 10) + '0');
		for(int j =0; j < DATA_LENGTH; j++){
			string[j] = num;
			if(j < sizeof(printer)){
				printer[j] = num;
			}
		}
		printer[sizeof(printer)] = '\0';
		if(enqueue_buffer_sem_syscall(string)){
			printf("::ENQUEUE::");
			printf("%s\n", printer);
		}else{
			i--;
		}
}
void *conthread(void *args){
	char temp[DATA_LENGTH];
	char printer[6];
	for(int i = 0; i < 1000; i++){
		sleep(((rand() % 10) + 1) * .001);
		if(dequeue_buffer_sem_syscall(temp) != -1){
			printf("::DEQUEUE::");
			for(int j = 0; j < sizeof(printer); j++){
				printer[j] = temp[j];
			}
			printer[sizeof(printer)] = '\0';
			printf("%s\n", printer);
		}
		else{
			i--;
		}
	}
}

int main(){
	init_buffer_sem_syscall();
	char temp[DATA_LENGTH];
	char insert[DATA_LENGTH];
	pthread_t producer, consumer;
	pthread_create(&producer, NULL, prothread, NULL);
	sleep(2);
	pthread_create(&consumer, NULL, conthread, NULL);
	delete_buffer_sem_syscall();
	return 0;
}
