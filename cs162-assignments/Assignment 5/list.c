/******************************************************
** Program: list.c
** Author: Logan Saso
** Date: 06/11/2017
** Description: Linked list implementation
** Input: none
** Output: none
******************************************************/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*********************************************************************
** Function: init
** Description: initializes head and tail
** Parameters: A list
** Pre-Conditions: none
** Post-Conditions: Head and tail are null
*********************************************************************/
void init(struct list *a_list)
{
	a_list->head = NULL;
	a_list->tail = NULL;
}

/*********************************************************************
** Function: size
** Description: Returns size of list
** Parameters: A list
** Pre-Conditions: none
** Post-Conditions: size returned
*********************************************************************/
int size(struct list a_list)
{
	if (empty(a_list))
	{
		return 0;
	}
	// printf("List is not empty.\n");
	struct node *curr = a_list.head; //sets current to beginning
	int counter = 0;
	while (curr->next != NULL)
	{
		counter++;
		curr = curr->next; //Sets current to next
	}
	return counter + 1;
}

/*********************************************************************
** Function: print
** Description: Print list
** Parameters: A list
** Pre-Conditions: none
** Post-Conditions: List printed
*********************************************************************/
void print(struct list a_list)
{
	struct node *curr = a_list.head; //sets current to beginning
	while (curr != NULL)
	{
		printf("%d\n", curr->val);
		curr = curr->next; //Sets current to next
	}
}

/*********************************************************************
** Function: push_front
** Description: Adds an item to the beginning of the list
** Parameters: A list, value
** Pre-Conditions: list initialized
** Post-Conditions: item added
*********************************************************************/
void push_front(struct list *a_list, int value)
{
	struct node *a_node = (struct node *)malloc(sizeof(struct node));
	a_node->val = value;		 //Sets value of new node to value
	a_node->next = a_list->head; //Sets value of new node next to first node
	a_list->head = a_node;		 //Sets value of list head to new first node
	if (a_list->tail == NULL)
		a_list->tail = a_node;
}

/*********************************************************************
** Function: push_back
** Description: Adds an item to the end of the list
** Parameters: A list, value
** Pre-Conditions: list initialized
** Post-Conditions: item added
*********************************************************************/
void push_back(struct list *a_list, int value)
{
	struct node *a_node = (struct node *)malloc(sizeof(struct node));
	a_node->val = value;
	a_node->next = NULL;			 //It's the last item in the list
	if (size(*a_list) > 0)			 //If the list is not empty (a last item exists)
		a_list->tail->next = a_node; //Set the previous last item's next to our new node (if exists)
	a_list->tail = a_node;			 //Set the tail to our new last node
	if (a_list->head == NULL)		 //If this is the first item we're adding
		a_list->head = a_node;		 //Set the head to the node also
}

/*********************************************************************
** Function: front
** Description: Returns first value from list
** Parameters: A list
** Pre-Conditions: none
** Post-Conditions: First item value returned
*********************************************************************/
int front(struct list a_list)
{
	if (empty(a_list))
	{
		return -1;
	}
	return a_list.head->val;
}

/*********************************************************************
** Function: back
** Description: Returns value of last item
** Parameters: A list
** Pre-Conditions: Items exist
** Post-Conditions: Last item value returned
*********************************************************************/
int back(struct list a_list)
{
	if (empty(a_list))
	{
		return -1;
	}
	return a_list.tail->val;
}

/*********************************************************************
** Function: pop_back
** Description: Pops last item from list
** Parameters: A list
** Pre-Conditions: none
** Post-Conditions: Last item is removed
*********************************************************************/
int pop_back(struct list *a_list)
{
	// printf("Popping Back.\n");
	int size_before = size(*a_list);
	if (empty(*a_list))
	{
		return -1;
	}
	// printf("Not Empty.\n");

	struct node *curr = a_list->head; //sets current to beginning
	struct node *prev = a_list->head;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next; //Sets current to next
	}					   //curr should be the last element at this point and prev should be the one before
	// printf("Location Got.\n");

	int val = curr->val;
	// printf("Val saved. %d\n", val);
	// printf("List Info: %d - %d - %d\n", a_list->head, a_list->tail, prev);
	prev->next = NULL;
	// printf("Prev next nulled.\n");

	a_list->tail = prev;
	// printf("tail prev.\n");
	free(curr);
	// printf("Freeing curr\n");
	if (size_before == 1)
	{
		a_list->tail = NULL;
		a_list->head = NULL;
	}
	return val;
}

/*********************************************************************
** Function: Remove front
** Description: removes first item from list
** Parameters: A list
** Pre-Conditions: List has an element
** Post-Conditions: List first element removed
*********************************************************************/
int remove_front(struct list *a_list)
{
	// printf("Removing front.\n");
	int size_before = size(*a_list);
	if (empty(*a_list))
	{
		return -1;
	}
	int val = a_list->head->val; //Stores value of first element
	// printf("Storing val.\n");
	struct node *first = a_list->head; //Stores memory location of first element
	// printf("Storing first location.\n");
	a_list->head = a_list->head->next; //Sets pointer of first location to next location
	// printf("Setting current head to next location.\n");
	free(first); //Deletes stored memeory location
	if (size_before == 1)
	{
		a_list->head = NULL;
		a_list->tail = NULL;
	}
	return val;
}

/*********************************************************************
** Function: Is linked list empty
** Description: Returns if the head is null
** Parameters: Takes a list
** Pre-Conditions: List exists
** Post-Conditions: List head returns true if head null
*********************************************************************/
int empty(struct list a_list)
{
	return a_list.head == NULL;
}

/*********************************************************************
** Function: Delete
** Description: Deletes the list
** Parameters: a linked list
** Pre-Conditions: Linked list exists 
** Post-Conditions: Linked list freed
*********************************************************************/
void delete (struct list *a_list)
{
	if (empty(*a_list))
	{
		free(a_list);
		return;
	}
	struct node *curr = a_list->head;
	while (a_list->head != NULL) //This works because we keep changing head
	{
		curr = a_list->head;
		a_list->head = a_list->head->next; //When head is last item, this will set it to null
		free(curr);
	}
	free(a_list);
	a_list = NULL;
}