/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Logan Saso
 * Email: logan.saso2016@gmail.com
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dynarray.h"

#include "pq.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq
{
  struct dynarray *heap;
};
struct process
{
  int pid;
};
struct proc
{
  int pid;
  int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq *pq_create()
{
  struct pq *pq = malloc(sizeof(struct pq) * 1);
  pq->heap = dynarray_create();
  return pq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq *pq)
{
  assert(pq);
  free(pq->heap);
  free(pq);
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq *pq)
{
  assert(pq);
  return dynarray_size(pq->heap) <= 0;
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
int parent_index(int index)
{
  return (index - 1) / 2;
}

void pq_insert(struct pq *pq, void *value, int priority)
{

  struct proc *new_process = malloc(sizeof(struct proc) * 1);      //Make a new process on the heap
  struct process *val = value;                                     //Sorta cast value to a process struct
  new_process->pid = val->pid;                                     //Setup our new process
  new_process->priority = priority;                                //Setup our new process
  dynarray_insert(pq->heap, dynarray_size(pq->heap), new_process); //Add our new process to the tree at the last value

  int index = dynarray_size(pq->heap) - 1;                           //Get the index of our new element. Since it's at the end, it's size - 1
  struct proc *current = dynarray_get(pq->heap, index);              //Get our new process's location in memory
  struct proc *parent = dynarray_get(pq->heap, parent_index(index)); //Get our new process's parent's location in memory

  while (current->priority < parent->priority && index >= 0)
  {                                                       //While the current node's priority is lower than its parent
    dynarray_set(pq->heap, parent_index(index), current); //Set the parent to what the current node points to
    dynarray_set(pq->heap, index, parent);                //Set the current to whatever the parent was

    index = parent_index(index);                          //After we move our element, set the index to the parent index
    parent = dynarray_get(pq->heap, parent_index(index)); //Get the parent of the new index and set it to local parent pointer
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void *pq_first(struct pq *pq)
{
  assert(pq && !pq_isempty(pq));
  return dynarray_get(pq->heap, 0);
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq *pq)
{
  assert(pq && !pq_isempty(pq));
  struct proc *process = pq_first(pq);
  return process->priority;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
int left_child_index(int index)
{
  return (2 * index) + 1;
}
int right_child_index(int index)
{
  return (2 * index) + 2;
}
int index_has_child(struct pq *pq, int index)
{
  return left_child_index(index) < dynarray_size(pq->heap) || right_child_index(index) < dynarray_size(pq->heap);
}

int has_two_children(struct pq *pq, int index)
{
  return left_child_index(index) < dynarray_size(pq->heap) && right_child_index(index) < dynarray_size(pq->heap);
}
int higher_priority_than_left_child(struct pq *pq, int index)
{
  if (left_child_index(index) >= dynarray_size(pq->heap))
  {
    return 0;
  }

  struct proc *parent = dynarray_get(pq->heap, index);
  struct proc *child = dynarray_get(pq->heap, left_child_index(index));
  return parent->priority > child->priority;
}
int higher_priority_than_right_child(struct pq *pq, int index)
{
  if (right_child_index(index) >= dynarray_size(pq->heap))
  {
    return 0;
  }

  struct proc *parent = dynarray_get(pq->heap, index);
  struct proc *child = dynarray_get(pq->heap, right_child_index(index));
  return parent->priority > child->priority;
}

int has_higher_priority_than_children(struct pq *pq, int index)
{
  return higher_priority_than_left_child(pq, index) || higher_priority_than_right_child(pq, index);
}

void *pq_remove_first(struct pq *pq)
{
  assert(pq && !pq_isempty(pq));

  struct proc *first = pq_first(pq);
  dynarray_set(pq->heap, 0, dynarray_get(pq->heap, -1)); //Copy the last value of the array to the root
  int index = 0;

  struct proc *current = dynarray_get(pq->heap, 0);

  struct proc *left_child;
  struct proc *right_child;

  while (index_has_child(pq, index) && has_higher_priority_than_children(pq, index) && index < dynarray_size(pq->heap))
  {

    #pragma region two children
    
    if (has_two_children(pq, index))
    {
      left_child = dynarray_get(pq->heap, left_child_index(index));
      right_child = dynarray_get(pq->heap, right_child_index(index));

      if (left_child->priority < right_child->priority)
      {
        dynarray_set(pq->heap, left_child_index(index), current);
        dynarray_set(pq->heap, index, left_child);
        index = left_child_index(index);
      }
      else
      {
        dynarray_set(pq->heap, right_child_index(index), current);
        dynarray_set(pq->heap, index, right_child);
        index = right_child_index(index);
      }
      continue;
    }

    #pragma endregion


    #pragma region one child

    if (left_child_index(index) < dynarray_size(pq->heap)) //If the one child it has is the left child
    {
      left_child = dynarray_get(pq->heap, left_child_index(index));
      dynarray_set(pq->heap, left_child_index(index), current);
      dynarray_set(pq->heap, index, left_child);
      index = left_child_index(index);
      continue;
    }

    if (right_child_index(index) < dynarray_size(pq->heap)) //If the one child it has is the right child
    {
      right_child = dynarray_get(pq->heap, right_child_index(index));
      dynarray_set(pq->heap, right_child_index(index), current);
      dynarray_set(pq->heap, index, right_child);
      index = right_child_index(index);
    }
    
    #pragma endregion
  
  }

  dynarray_remove(pq->heap, -1); //Remove last item from the heap

  return first;
}
