#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "queue.h"

#define QUEUE_MAX_LENGTH 1000

/**
 ** -------------                    -----------------  
 ** | a | b | c |   enqueue('d') ->  | a | b | c | d |  
 ** -------------                    -----------------  
 **   ^         ^                      ^           ^
 **   |         |                      |           |
 **   front    rear                  front        rear  
 **
 **
 ** LIFO mode
 **                   -------------
 **     dequeue() --> | b | c | d |
 **     returns 'a'   -------------
 **				^
 **                     |
 **                   front
 **
 ** FIFO mode
 **                   -------------
 **     dequeue() --> | a | b | c |
 **     returns 'd'   -------------
 **                             ^
 **                             |
 **                            rear
 **/

/**
 ** @brief a simple DS for a queue
 **/
struct queue {
  queue_element_type* values [QUEUE_MAX_LENGTH];
  xifo  type; /* can be FIFO or LIFO (LIFO is equivalent to a stack) */
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
  assert(q);
  if(q->rear==QUEUE_MAX_LENGTH)
      return -1;
  q->values[q->rear++] = n;
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
  queue_element_type *n;

  assert(q);   
  
  if (q->rear==q->front) /* empty queue */
    return 0;

  switch (q->type) {
  case lifo : q->rear--; 
		  n = q->values[q->rear];
             break;
  case fifo : n = q->values[q->front++];    
             break;
  }
  return n;
}


/**
 * @brief remove the first element in queue.
 * @return -1 if queue is empty, 0 otherwise.
 **/
int queue_remove(queue *q) {
    assert(q);
    if (q->front == q->rear)
        return -1;
    q->front++;
    return 0;
}


/**
 ** @brief tell the queue length.
 ** @return a non-null integer corresponding to the length
 **/
size_t queue_length(queue *q) {
  assert(q);
  assert(q->rear>=q->front);
  return(q->rear - q->front);
}

/**
 *  @brief is the queue empty ? 
 *  The queue is assumed to be existing.
 *  @return true if the queue is empty, false otherwise. 
 **/
bool queue_isempty(queue *q) {
  assert(q);
  return (q->front == q->rear);
}


/**
 * @brief delete the whole queue
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
#else
	printf("arbre @%p",q->values[i]);
#endif
      printf("|");
    }
    printf(" front/rear=%d/%d\n",q->front,q->rear);
}

/**
 ** @brief display the contents of the queue @a queue using print function @a f
 **/ 
void queue_print_generic(queue *q, void (*printfn)(void *data)) {
    int i;
    printf("|");
    for(i = q->front; i < q->rear; i++) {
      // for trees 
	printfn(q->values[i]);
      printf("|");
    }
    printf(" front/rear=%d/%d\n",q->front,q->rear);
}
