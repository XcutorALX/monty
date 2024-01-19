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
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		freeMem();
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
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
		freeMem();
		exit(EXIT_FAILURE);
	}

	current = *stack;

	if (current->prev == NULL && info->mode == 's')
	{
		free(current);
		*stack = NULL;
		return;
	}
	else if (info->mode == 'q' && current->next == NULL)
	{
		free(current);
		*stack = NULL;
		return;
	}

	if (info->mode == 's')
	{
		current->prev->next = NULL;
		*stack = current->prev;
	}
	else
	{
		current->next->prev = NULL;
		*stack = current->next;
	}
	free(current);
}

/**
 * pall - prints all values on stack
 *
 * @stack: the current stack
 * @line_number: the current line being executed
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (info->command == NULL)
	{
		fprintf(stderr, "Error: L%u\n", line_number);
		freeMem();
		exit(EXIT_FAILURE);
	}

	if (*stack == NULL)
		return;

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);

		if (info->mode == 's')
			current = current->prev;
		else
			current = current->next;
	}
}

/**
 * push - pushes an element onto the stack
 *
 * @line_number: the current line
 * @stack: program stack
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *current, *new;
	int argument;

	info->errorno = 0;
	argument = _atoi(info->command[1]);
	if (info->errorno == -1)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		freeMem();
		exit(EXIT_FAILURE);
	}

	new = malloc(sizeof(stack_t));
	if (!new)
		exit(EXIT_FAILURE);
	new->n = argument;
	new->next = NULL;
	new->prev = NULL;

	if (*stack == NULL)
	{
		*stack = new;
		return;
	}

	current = *stack;

	if (info->mode == 's')
		*stack = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
	}

	new->prev = current;
	current->next = new;
}

/**
 * swap - swaps the top two elements of the stack
 *
 * @line_number: the current line
 * @stack: the program stack
 */

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *current;
	int i, temp;

	current = *stack;
	for (i = 0; *stack != NULL && current != NULL; i++)
	{
		if (info->mode == 's')
			current = current->prev;
		else
			current = current->next;
	}


	if (i < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n",
				line_number);
		freeMem();
		exit(EXIT_FAILURE);
	}

	current = *stack;
	temp = current->n;
	if (info->mode == 's')
	{
		current->n = current->prev->n;
		current->prev->n = temp;
	}
	else
	{
		current->n = current->next->n;
		current->next->n = temp;
	}
}
