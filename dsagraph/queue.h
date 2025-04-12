/**
 * \file queue.h
 */
#include <stdbool.h>

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

/* The following line parameterizes the type of elements handled in queue */
/* instructions : define the right symbol in the calling program (the one with the main()) */

#define  __QUEUES_OF_ADJNODES__  // define it here of in Makefile with -D
#ifdef  __QUEUES_OF_ADJNODES__ 
#include "graph.h"
typedef info_node queue_element_type;
#endif


typedef struct queue queue;
enum xifo { fifo , lifo };
typedef enum xifo xifo;

/**
  * @brief creates a queue of the given type @a typexifo
  * @param[in] type The mode for the queue (fifo or lifo).
  * @return a reference to the newly created queue.
 **/
queue* queue_create(xifo type);

/**
 * @brief enqueue a queue_element_type @a n in queue @a q.
 * \pre queue q exists.
 * @param[out] queue @a q is supposed be created through queue_init().
 * @return -1 if max capacity is reached, 0 otherwise.
 */
int queue_enqueue(queue *q,queue_element_type *e);

/**
 * @brief dequeue a queue_element_type @a n from queue @a q.
 * \pre queue q exists.
 * @param[out] queue @a q is supposed be created through queue_init().
 * @return NULL if the queue is empty, the last enqueued element
 * for a LIFO queue, the first enqueued element for a LIFO queue.
 */
queue_element_type *queue_dequeue(queue *q);

/**
 * @brief remove the first element in queue.
 * \pre queue q exists.
 * @return -1 if queue is empty, 0 otherwise.
 */
int queue_remove(queue *q);

/**
 ** @brief tell the queue length.
 * \pre queue q exists.
 ** @return a non-null integer corresponding to the length
 **/
size_t queue_length(queue *q);

/**
  *  @brief is the queue empty ? 
  * \pre queue q exists.
  *  @return true if the queue is empty, false otherwise. 
  */
bool   queue_isempty(queue *q);

/**
 * @brief delete the whole queue @a q
 **/
void queue_delete(queue *q);

/**
  * @brief display the contents of the queue @a queue 
  */ 
void queue_print(queue *q);

/**
  * @brief display the contents of the queue @a queue using print function @a f
  */ 
void queue_print_generic(queue *q,void (*printfn)(void *data));
