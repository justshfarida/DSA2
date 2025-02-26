#include<assert.h>
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "queue.h"

#define QUEUE_MAX_LENGTH 1000

/**
 ** @brief a simple DS for a queue
 **/
struct queue {
  
  queue_element_type *values [QUEUE_MAX_LENGTH]; /*< an array of pointers to the values to store */
  xifo  type;                                    /*< can be FIFO or LIFO (LIFO is a  stack) */
  int   rear;
  int   front;
};


/**
 ** @brief creates a queue of the given type @a typexifo
 ** @return a reference to the newly created queue.
 **/
queue* queue_create(xifo typexifo) {

    queue *q = malloc(sizeof(*q));
 
    /* Initializes the whole structure. */
    *q = (queue){
      .values = {0},
      .type = typexifo,
      .rear   = 0,
      .front  = 0,
    };
  return q;
}


/**
 * @brief enqueue a queue_element_type @a n in queue @a q.
 * Queue @a q is supposed be created through queue_create().
 * @return -1 if max capacity is reached, 0 otherwise.
 **/
int queue_enqueue(queue *q, queue_element_type *n) {

   // ... complete ...
         
   // Check if queue is full
   if (q->rear >= q->front+QUEUE_MAX_LENGTH) {
      return -1;
   }
   // Add the new element to the queue
   // ... complete...a
   q->values[q->rear]=n;
   q->rear++;
   return 0;
}



/**
 * @brief dequeue a queue_element_type @a n from queue @a q.
 * Queue @a q is supposed be created through queue_init().
 *
 * @return NULL if the queue is empty, the last enqueued element
 * for a LIFO queue, the first enqueued element for a LIFO queue.
 **/
queue_element_type *queue_dequeue(queue *q) {

   // ... complete ...
   //
   queue_element_type *n;
   // Check if queue is empty
   if (q->front == q->rear) {
      return NULL;
   }
   if(q->type==1)
   {
      n = q->values[q->rear-1];  // LIFO last element is at rear-1 position.
      q->rear--;
   }
   else if (q->type==0)
   {
      n = q->values[q->front];
      q->front++;
   }
   return n;
}


/**
 * @brief remove the first element in queue.
 * @return -1 if queue is empty, 0 otherwise.
 **/
int queue_remove(queue *q) {

   // ... complete ...
   //
   
   return 0;
}


/**
 ** @brief tell the queue length.
 ** @return a non-null integer corresponding to the length
 **/
size_t queue_length(queue *q) {


   // ... complete ...
   //
   int length=q->rear-q->front;
   return length;

}

/**
 *  @brief is the queue empty ? 
 *  The queue is assumed to be existing.
 *  @return true if the queue is empty, false otherwise. 
 **/
bool queue_isempty(queue *q) {

   // ... complete ...
   //
   if(q->front==q->rear)
   {
      return true;
   }
   return false;

}


/**
 * @brief delete the whole queue
 * \pre the queue must exist.
 **/
void queue_delete(queue *q) {
    assert(q);
    free(q->values);
}


/**
 ** @brief display the contents of the queue @a queue 
 ** \warning{ For a sake of simplicity, this function only works for queues of ints.}
 **/ 
void queue_print(queue *q) {
    int i;
    printf("|");
    for(i = q->front; i < q->rear; i++) {
#ifdef __QUEUES_OF_INTS__
	printf("%d",*(q->values[i]));
#endif
      printf("|");
    }
    printf(" front/rear=%d/%d\n",q->front,q->rear);
}

