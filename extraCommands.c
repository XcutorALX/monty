#include "monty.h"

/**
 * rotr - rotates the stack to the bottom
 *
 * @stack: current stack
 * @line_number: current line
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *current, *bottom, *second;

	if (line_number <= 0)
		return;

	if (*stack == NULL)
		return;
	else if ((*stack)->next == NULL && (*stack)->prev == NULL)
		return;

	bottom = *stack;
	for (current = *stack; current != NULL;)
	{
		bottom = current;
		if (info->mode == 's')
			current = current->prev;
		else
			current = current->next;
	}

	current = *stack;
	if (info->mode == 's')
	{
		second = bottom->next;
		bottom->prev = current;
		bottom->next = NULL;
		current->next = bottom;
		second->prev = NULL;
		*stack = bottom;
	}
	else
	{
		second = bottom->prev;
		bottom->next = current;
		bottom->prev = NULL;
		current->prev = bottom;
		second->next = NULL;
		*stack = bottom;
	}
}
