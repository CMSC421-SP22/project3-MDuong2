#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_init_buffer_421 442
long init_buffer_syscall(void){
	return syscall(__NR_init_buffer_421);
	}
#define __NR_insert_buffer_421 443
long insert_buffer_syscall(int i){
	return syscall(__NR_insert_buffer_421, i);
}
#define __NR_print_buffer_421 444
long print_buffer_syscall(void){
	return syscall(__NR_print_buffer_421);
}
#define __NR_delete_buffer_421 445
long delete_buffer_syscall(void){
	return syscall(__NR_delete_buffer_421);
}


int main(){
	if(print_buffer_syscall() != -1){
		printf("Fails no buffer print test\n");
	}
	if(insert_buffer_syscall(45) != -1){
		printf("Fails no buffer insert test\n");
	}
	if(delete_buffer_syscall() != -1){
		printf("Fails no buffer delete test\n");
	}
	init_buffer_syscall();
	for(int i = 0; i < 20; i++){
		insert_buffer_syscall(i);
	}
	if(insert_buffer_syscall(45) != -1){
		printf("Fails over insert test\n");
	}
	delete_buffer_syscall();
	printf("Default test\n");
	printf("use sudo dmesg\n");
	if(init_buffer_syscall() == 0){
		for(int i =0; i < 20; i++){
			insert_buffer_syscall(i);
		}
		print_buffer_syscall();
		delete_buffer_syscall();
		return 0;
	}
	delete_buffer_syscall();
}

