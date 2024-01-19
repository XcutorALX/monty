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

/**
 * stack - sets the format of the data to a stack (LIFO)
 *
 * @stack: the current stack
 * @line_number: the current line
 */

void stack(stack_t **stack, unsigned int line_number)
{
	stack_t *bottom, *temp, *prev;

	if (line_number <= 0)
		return;

	if (info->mode == 's')
		return;

	info->mode = 's';
	if (*stack == NULL)
		return;

        for (bottom = *stack; bottom->next != NULL;
			bottom = bottom->next)
		;

	temp = NULL;
	prev = NULL;
	while (bottom != NULL)
	{
		temp = bottom;
		bottom = bottom->prev;
		temp->next = (bottom != NULL) ? bottom : NULL;
		temp->prev = prev;
		prev = temp;

	}
	*stack = temp;
	
}

/**
 * queue - sets the format of the data to a queue (FIFO)
 *
 * @stack: the current stack
 * @line_number: the current line
 */

void queue(stack_t **stack, unsigned int line_number)
{
        stack_t *bottom, *temp, *prev;

	if (line_number <= 0)
		return;

	if (info->mode == 'q')
		return;

	info->mode = 'q';
	if (*stack == NULL)
		return;

	for (bottom = *stack; bottom->prev != NULL;
			bottom = bottom->prev)
		;

	temp = NULL;
	prev = NULL;
	while (bottom != NULL)
	{
		temp = bottom;
		bottom = bottom->next;
		temp->prev = (bottom != NULL) ? bottom : NULL;
		temp->next = prev;
		prev = temp;
	}
	*stack = temp;
}
