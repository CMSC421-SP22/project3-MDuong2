#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int main(){
	printf("Main\n");
	{
	init_buffer_421();
	for(int i = 0; i < 10 ; i++){
		insert_buffer_421(i);
		}
	print_buffer_421();
	insert_buffer_421(11+1);
	print_buffer_421();
	delete_buffer_421();
	print_buffer_421();
	}
	//TEST CASE 1: Enter Data Before Buffer

	printf("1\n");
	{
		if(insert_buffer_421(12) != -1){
			printf("Test Case 1: Fail\n");
		}else{
			printf("Test Case 1: Pass\n");
		}
	}

	//Test Case:	Delete without buffer
	{
		if(delete_buffer_421() != -1){
			printf("delete fail\n");
		}
		else{
			printf("pass delete without buffer\n");
		}
	}
//Test case standard
	{
	printf("Standard Test\n");
	init_buffer_421();
	int x = 0; int y = 0;
	for(int i = 0; i < 5; i++){
		if(insert_buffer_421(i) != -1){
			printf("Successful insert\n");
			x = 1;
		}
	}
	if(delete_buffer_421() != -1){
		printf("std delete passed\n");
		y = 1;
	}
	if(x == 1 && y == 1){
		printf("std test passed\n");
		}
	delete_buffer_421();
	}

//	Test Case 2: Making another buffer
	printf("2\n");
	{
		if(init_buffer_421() == 0){
			if(init_buffer_421() != -1){
				printf("Test Case 2: Fail\n");
			}else{
			printf("Test Case 2: Pass\n");
			}
		}
		delete_buffer_421();
	}
//	Test Case 3: Extra insertion
	printf("Test 3\n");
	{
		init_buffer_421();
		for(int i = 0; i < 30; i++){
			if(insert_buffer_421(i) != -1){
				if(i == 20){
					printf("Test Case 3: Passed\n");
				}
			}
		}
		delete_buffer_421();
	}
	//Test Case 4: Prints without a buffer
	{	if(print_buffer_421() != -1){
			printf("Test Case 4: Failed\n");
		}else{
			printf("Test Case 4: Passed\n");
		}
	}
	//Test Case 5: Delete without buffer
	{	if(delete_buffer_421() != -1){
			printf("Test Case 5: failed\n");
		}else{
			printf("Test Case 5: Passed\n");
		}
	}
	//Test 
	printf("Test 6\n");
	init_buffer_421();
	for(int i =  0; i < 5; i++){
		insert_buffer_421(i);
		print_buffer_421();
		printf("\n\n\n");
	}
	delete_buffer_421();
	printf("Cases Pased\n");
	return 0;
}
