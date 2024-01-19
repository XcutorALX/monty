#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * arit - performs arithmetic operations
 *
 * @stack: the current stack
 * @line_number: current line number
 *
 */

void arit(stack_t **stack, unsigned int line_number)
{
        stack_t *current;
        int result, i;
	char *operation;

	operation = info->command[0];
        current = *stack;
        for (i = 1; *stack != NULL && current->next != NULL;
                        current = current->next, i++);

	if (i < 2)
	{
		fprintf(stderr, "L%u: can't %s, stack too short\n",
                                line_number, operation);
		freeStack();
		freeMem();
		exit(EXIT_FAILURE);
	}

	if (strcmp(operation, "add") == 0)
		result = current->prev->n + current->n;
	else if (strcmp(operation, "sub") == 0)
		result = current->prev->n - current->n;
	else if (strcmp(operation, "div") == 0)
	{
		fprintf(stderr, "L%u: division by zero\n",
				line_number);
		freeMem();
		freeStack();
		exit(EXIT_FAILURE);
	}
	else if (strcmp(operation, "mod") == 0)
		result = current->prev->n % current->n;
	else if (strcmp(operation, "mul") == 0)
		result = current->prev->n * current->n;

	current->prev->n = result;
	current->prev->next = NULL;
	free(current);
}

