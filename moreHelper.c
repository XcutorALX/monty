#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * freeStack - frees the stack
 */

void freeStack(void)
{
	stack_t *current, *temp;

	current = info->stack;

	if (current == NULL)
		return;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
