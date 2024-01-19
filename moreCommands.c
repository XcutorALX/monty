#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * adds - adds the top two elements of the stack
 *
 * @stack: the current stack
 * @line_number: current line number
 */

void add(stack_t **stack, unsigned int line_number)
{
	stack_t *current;
	int result, i;

	current = *stack;
	for (i = 1; *stack != NULL && current->next != NULL;
			current = current->next, i++);

	if (i < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n",
				line_number);
		freeStack();
		freeMem();
		exit(EXIT_FAILURE);
	}

	result = current->n + current->prev->n;
	current->prev->n = result;
	current->prev->next = NULL;
	free(current);
}

/**
 * sub - subtracts the top two elements of the stack
 *
 * @stack: the current stack
 * @line_number: current line number
 */

void sub(stack_t **stack, unsigned int line_number)
{
        stack_t *current;
        int result, i;

        current = *stack;
        for (i = 1; *stack != NULL && current->next != NULL;
                        current = current->next, i++);

        if (i < 2)
        {
                fprintf(stderr, "L%u: can't add, stack too short\n",
                                line_number);
                freeStack();
                freeMem();
                exit(EXIT_FAILURE);
        }

        result = current->prev->n - current->n;
        current->prev->n = result;
        current->prev->next = NULL;
	free(current);
}
