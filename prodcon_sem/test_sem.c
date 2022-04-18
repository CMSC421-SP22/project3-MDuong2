#include <stdio.h>
#include <stdlib.h>
#include <buffer_sem.h>

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
long delete_buffer_sem_421(void){
	return syscall(__NR_delete_buffer_sem_421);
}


int main(){
	printf("main");
}
