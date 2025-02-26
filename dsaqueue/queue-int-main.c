/**
 *
 * \file queue-int-main.c
 *
 * This file provide a main() function to test the queue data structure
 * with ints as values in the queues.
 *
 **/

#include <stdio.h>
#include "queue.h"

/* N O T I C E
 * At compile-time, queue.h should be configured to store struct node as values.
 * See queue.h to check what symbol guards the definition
 *   typedef int queue_element_type;
 * (currently __QUEUES_OF_INTS__)
 *
 * Configuration is done through conditional compilation (using #ifdef symbols)
 * You might want to define the symbol at compile time :
 * gcc -D__QUEUES_OF_INTS__ queue-int-main.c queue.c -o queue-int-main
 */

 


#define MAX_VAL 5

int main() {
int v [MAX_VAL];


  printf("\n* Creating FIFO queue ...\n");
  queue *myqueue = queue_create( fifo );

  printf("\n* Going to enqueue 1, 2,..., %d into the FIFO queue ...\n",MAX_VAL);

  for (size_t i=0;i<MAX_VAL;i++) {
	v[i]=i+1;
  	printf("\n** Enqueueing val=%d\n",v[i]);
      queue_enqueue(myqueue, &(v[i]));
      queue_print(myqueue);
      printf("** Queue len:%zu\n",queue_length(myqueue));
  }

  printf("\n* Going to dequeue 5 times the FIFO queue ...\n");
  for (size_t i=0;i<MAX_VAL;i++) {
	queue_element_type *d = queue_dequeue(myqueue);
      queue_print(myqueue);
	if ( NULL != d) 
  		printf("\n** Got val=%d\n",*d);
	else
  		printf("\n** Could not dequeue an element : queue was empty !\n");
      printf("** Queue len:%zu\n",queue_length(myqueue));
  }

  queue_delete(myqueue);
}
