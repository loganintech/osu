/******************************************************
** Program: stack.c
** Author: Logan Saso
** Date: 06/11/2017
** Description: Runs a stack testing program 
** Input: [({})] symbols
** Output: Whether or not it's a valid [({})]
******************************************************/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************
** Function: value(char c)
** Description: Takes a character returns the corresponding character
** Parameters: a character
** Pre-Conditions: a character exists
** Post-Conditions: the value is returned
*********************************************************************/
int value(char c)
{
	switch (c)
	{
	case '{':
		return 0;
	case '}':
		return 1;
	case '[':
		return 4;
	case ']':
		return 5;
	case '(':
		return 8;
	case ')':
		return 9;
	}
	return -1;
}

/*********************************************************************
** Function: Main
** Description: Runs the logic of the stack
** Parameters: argc, argv
** Pre-Conditions: none
** Post-Conditions: String is valid or invalid
*********************************************************************/
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("You need to include a parameter consisting of [({... All other characters make your string invalid.");
		return 1;
	}

	struct list *a_list = (struct list *)malloc(sizeof(struct list));
	init(a_list);

	printf("Your argument: ");
	printf(argv[1]);
	printf("\n");

	int i;
	for (i = 0; i < strlen(argv[1]); i++)
	{
		if (value(argv[1][i]) % 2 == 0) //Even is an opening thing
		{
			push_back(a_list, value(argv[1][i]));
		}
		else //Odd is a closing thing
		{
			if (back(*a_list) == value(argv[1][i]) - 1)
			{ //They match
				pop_back(a_list);
			} // Otherwise it's probably invalid
		}
		// printf("\n\n\n\n");
	}

	if (empty(*a_list))
	{
		printf("Your string is valid.\n");
	}
	else
	{
		printf("Your string is invalid.\n");
	}
	delete (a_list);
}
