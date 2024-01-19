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
	stack_t *current, *second;
	int result, i;
	char *operation;

	current = *stack;
	operation = info->command[0];
	for (i = 0; *stack != NULL && current != NULL; i++)
	{
		if (info->mode == 's')
			current = current->prev;
		else
			current = current->next;
	}

	if (i < 2)
	{
		fprintf(stderr, "L%u: can't %s, stack too short\n",
				line_number, operation);
		freeMem();
		exit(EXIT_FAILURE);
	}
	
	current = *stack;
	result = aritHelper(&second);
	if (info->mode == 's')
		second->next = NULL;
	else
		second->prev = NULL;
	second->n = result;
	*stack = second;
	free(current);
}

/**
 * aritHelper - breaks down the arithmetic process
 *
 * @second: a pointer to the second element on the stack
 *
 * Return: returns the result from the arithmetic process
 */

int aritHelper(stack_t **second)
{
	stack_t *current;
	char *operation;
	int result;

	operation = info->command[0];
	current = info->stack;
	if (info->mode == 's')
		*second = current->prev;
	else
		*second = current->next;
	if (strcmp(operation, "add") == 0)
		result = (*second)->n + current->n;
	else if (strcmp(operation, "sub") == 0)
		result = (*second)->n - current->n;
	else if (strcmp(operation, "div") == 0)
	{
		if (current->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n",
				info->line);
			freeMem();
			exit(EXIT_FAILURE);
		}
		result = (*second)->n / current->n;
	}
	else if (strcmp(operation, "mod") == 0)
	{
		if (current->n == 0)
		{
			fprintf(stderr, "L%u: division by zero\n",
					info->line);
			freeMem();
			exit(EXIT_FAILURE);
		}
		result = (*second)->n % current->n;
	}
	else if (strcmp(operation, "mul") == 0)
		result = (*second)->n * current->n;
	return (result);
}

/**
 * pchar - prints the char at the top of the stack followed by a new line
 *
 * @stack: the program stack
 * @line_number: the current line number
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n",
				line_number);
		freeStack();
		freeMem();
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n >= 0 && (*stack)->n <= 127)
	{
		printf("%c\n", (*stack)->n);
		return;
	}

	fprintf(stderr, "L%u: can't pchar, value out of range\n",
			line_number);
	freeStack();
	freeMem();
	exit(EXIT_FAILURE);
}
