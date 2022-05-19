/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "queue.h"
#include "stack_from_queues.h"

#pragma region create

/*
 * This function should allocate and initialize all of the memory needed for
 * your stack and return a pointer to the stack structure.
 */
struct stack_from_queues *stack_from_queues_create()
{
  struct stack_from_queues *stack = malloc(sizeof(struct stack_from_queues));

  stack->q1 = queue_create();
  stack->q2 = queue_create();

  return stack;
}

#pragma endregion

#pragma region free
/*
 * This function should free all of the memory allocated to a stack, including
 * the memory associated with each queue.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.  The function should
 *     exit the program with an error if stack is NULL.
 */
void stack_from_queues_free(struct stack_from_queues *stack)
{
  assert(stack != NULL);
  queue_free(stack->q1);
  queue_free(stack->q2);
  free(stack);
}

#pragma endregion

#pragma region isempty
/*
 * This function should return 0 if a stack is completely empty or 1 if there
 * is at least one element stored in the stack.
 *
 * Params:
 *   stack - the stack whose emptiness is to be checked.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *
 * Return:
 *   Should return 0 if the stack is empty or 1 otherwise.
 */
int stack_from_queues_isempty(struct stack_from_queues *stack)
{
  assert(stack != NULL);
  return queue_isempty(stack->q1) && queue_isempty(stack->q2);
}

#pragma endregion

#pragma region push
/*
 * Should push a new value onto a stack.
 *
 * Params:
 *   stack - the stack onto which to push a value.  May not be NULL.
 *     The function should exit the program with an error if stack is NULL.
 *   value - the new value to be pushed onto the stack
 */
void stack_from_queues_push(struct stack_from_queues *stack, int value)
{
  assert(stack != NULL);

  queue_enqueue(stack->q2, value);
  while (!queue_isempty(stack->q1))
  {
    queue_enqueue(stack->q2, queue_dequeue(stack->q1));
  }

  struct queue *temp;
  temp = stack->q2;
  stack->q2 = stack->q1;
  stack->q1 = temp;
}

#pragma endregion

#pragma region top
/*
 * Should return a stack's top value without removing that value from the
 * stack.
 *
 * Params:
 *   stack - the stack from which to read the top value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack.
 */
int stack_from_queues_top(struct stack_from_queues *stack)
{
  assert(stack != NULL && !stack_from_queues_isempty(stack));

  int top = 0;
  while (!queue_isempty(stack->q1))
  {
    if (!queue_isempty(stack->q2))
    {
      top = queue_front(stack->q2);
    }
    queue_enqueue(stack->q2, queue_dequeue(stack->q1));
  }

  struct queue *temp;
  temp = stack->q2;
  stack->q2 = stack->q1;
  stack->q1 = temp;

  return top;
}

#pragma endregion

#pragma region pop
/*
 * Should remove the top element from a stack and return its value.
 *
 * Params:
 *   stack - the stack from which to pop a value.  May not be NULL or
 *     empty.  The function should exit the program with an error if stack is
 *     NULL or empty.
 *
 * Return:
 *   Should return the value stored at the top of the stack before that value
 *   is popped.
 */
int stack_from_queues_pop(struct stack_from_queues *stack)
{
  assert(stack != NULL && !stack_from_queues_isempty(stack));
  return queue_dequeue(stack->q1);
}

#pragma endregion
