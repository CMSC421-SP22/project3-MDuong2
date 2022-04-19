This is the README file for PRODCON_MON

To solve the issue of not using semaphores within our producer and consumer and using monitors instead was started by porting over the user space code
from the semaphore directory and making some alterations to it. Once again using the pthread library and some of its built in functions including 
its mutex and conditional variable functions I created two conditional variables. Very similarly to the semaphore version we must lock our buffer from
being inserted and deleted from at the same time. This is solved by using the mutex that we created that forces only one of these processes to happen at
a time. The conditional variables are used within a loop so that if our buffer is full or empty and we try to insert or delete respectively and we are
not able to do that then, it moves the mutex along without removing the lock on it by using another pthread function. This part is critical to ensure
that we do not have our program get stuck in an infinite loop. Another thing that was within the project specifications was that there is a 0 - 10
millisecond delay between our runs of enqueues or dequeues. By using the random function and some math we are able to accurately wait between 10 and 0 
milliseconds. I knew I had to use conditional variables for this part with monitors because of a few factors. First of which is spin waiting although
this one doesn't have the potential to reach an insecure state it is a waste of resources. Another, possible solution could have been busy waiting 
although initially it seems more promising than it actually is. This implementation's largest issue is that accesses to enqueue can be interrupted by 
other threads that can interleave those threads access to the enqueuing process. This can lead to race conditions, errors and many other things. Thusly
using conditional variables was not only the most efficent option but also the best. 



Within our buffer_mon.c file we have the same functions as within our prodcon_user_sem with the exception of print_semaphores(). These do the same
things. Our init_buffer function creates our bounded buffer that has upto 20 fillable nodes that can contain upto 1024 characters. In addition, this 
memory allocated, and set as a 0. The initialization function can have one buffer at a time. Therefore, if you were to try to create a new buffer
when one already exists it would not create one. For the next functions within this are our enqueue and dequeue functions. These insert data of 1024
characters and delete them from the buffer respectively. Another thing that these functions do is increase the size or decrease the size of our buffer.
Lastly, we have our delete buffer function that deletes any of the memory that we have allocated. 

How to run test file
	test_mon.c
		gcc test_mon.c -o test_mon -lpthread
