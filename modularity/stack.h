#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/** 
 * @brief Definition of a stack type
 */
typedef struct stack_t * stack;

/** 
 * @brief Creates an empty stack
 * @return A new empty stack
 */
stack create(void);

/** 
 * @brief Checks if a stack is empty
 * @param s The stack to check
 * @return true if the stack is empty, false otherwise
 */
bool is_empty(stack s);

/** 
 * @brief Pushes an integer onto the stack
 * @param sp A pointer to the stack
 * @param val The value to push onto the stack
 */
void push(stack * sp, int val);

/** 
 * @brief Pops an integer from the stack
 * @param sp A pointer to the stack
 * @return The popped value
 * @note This function assumes the stack is not empty
 */
int pop(stack * sp);

#endif
