This is my readme file for part 2 of the project 3 within prodcon_sem directory. 

Overview of what this part does 
	1) uses the buffer struct that we used in buffer
	2) uses semaphores and pthread to concurrently consume and produce nodes inside of the buffer
	3) waits between 0 and 10 milliseconds between inserts and deletes from the buffers
Inside of buffer_user_sem.c
	{
init_buffer_421
	This function creates our buffer. It also sets the values for our semaphores that will be used to keep track of the state of our operations.
One of these is the amount of nodes that are full, and another are the amount of nodes that are empty. The buffer will not be created if a buffer 
already exists. The data that the nodes can contain are strings of characters whose length is 1024.
	
enqueue_buffer_421
	This function is used to add data into our buffer. By using our mutal exclusion semaphore we are able to ensure that this is the only process
happening if we pass our two test conditions. These conditions are that the buffer exists and the buffer is not full, if either of these are true
then we exit the function. If we are able to insert new data then we increase the size of our buffer, add the data at the current point and then alter
the state of our semaphores that keep track of the state of our nodes.

dequeue_buffer_421
	For this function we also have to check our conditions that the buffer exists and there are nodes to dequeue. If neither of the conditions are
met then, we are unable to dequeue anything from the buffer. This function takes the information from within the buffer and exports it to our data 
then removes the information from the buffer as it has been used. Then, we decrease the size of the buffer by one. 
delete_buffer_421
	This is our final function that deletes our buffer. Again we must ensure that our buffer exists. If it does not we cannot destroy it. Otherwise
using a similar process to creating it we ensure that all information and nodes are destroyed properly and that there is no more allocated memory. This
makes sure that we have no memory leaks or wasted resources on processes that no longer are needed.
	}
