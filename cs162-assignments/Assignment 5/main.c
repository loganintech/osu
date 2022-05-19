#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Program starting\n");
	struct list *a_list = (struct list *)malloc(sizeof(struct list));
	init(a_list);
	if (empty(*a_list))
	{
		printf("List is empty.\n");
	}
	print(*a_list);
	push_back(a_list, 12);
	print(*a_list);
	push_back(a_list, 3);
	print(*a_list);
	push_back(a_list, 5);
	print(*a_list);
	delete_node(1, a_list);
	print(*a_list);

	if (empty(*a_list))
	{
		printf("List is empty.\n");
	}

	delete (a_list);
	return 0;
}