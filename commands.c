#include "monty.h"
#include <stdlib.h>

/**
 * pint - prints the top of the stack
 *
 * @line_number: the current line
 * @stack: the program stack
 */

void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty", line_number);
		exit(EXIT_FAILURE);
	}

	current  = *stack;
	while (current->next != NULL)
		current = current->next;

	printf("%d\n", current->n);
}
