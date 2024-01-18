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
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	current  = *stack;
	while (current->next != NULL)
		current = current->next;

	printf("%d\n", current->n);
}

/**
 * pop - removes the top element of the stack
 *
 * @line_number: the current line
 * @stack: the program stack
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	current = *stack;

	while (current->next != NULL)
		current = current->next;

	current->prev->next = NULL;
	free(current);
}

/**
 * freeStack - frees the stack
 */

void freeStack(void)
{
	stack_t *current, *temp;

	current = info->programStack;
	
	if (current == NULL)
		return;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
