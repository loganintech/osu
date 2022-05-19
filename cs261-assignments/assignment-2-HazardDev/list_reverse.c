/*
 * This is the file in which you'll write a function to reverse a linked list.
 * Make sure to add your name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdio.h>

#include "list_reverse.h"

/*
 * In this function, you will be passed the head of a singly-linked list, and
 * you should reverse the linked list and return the new head.  The reversal
 * must be done in place, and you may not allocate any new memory in this
 * function.
 *
 * Params:
 *   head - the head of a singly-linked list to be reversed
 *
 * Return:
 *   Should return the new head of the reversed list.  If head is NULL, this
 *   function should return NULL.
 */
struct link* list_reverse(struct link* head) {

    if (head == NULL) {
        
        return NULL;
   
    }   

    struct link *curr = NULL;
    struct link *next = head;
    struct link *temp;  

    while (next->next != NULL) {

        temp        = next->next;
        next->next  = curr;
        curr        = next;
        next        = temp;

    }   

    next->next  = curr;
    head        = next;  

    return head;
  
}


