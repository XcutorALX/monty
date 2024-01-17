#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * readCode - gets the op code from the specified file
 *
 * @info: the info needed to for the program to run
 *
 * Return: returns -1 on failure
 */

int readCode(info_t *info)
{
	char *lineptr, *delim;
	size_t n, line;
	FILE *stream;

	delim = " ";
	line = 1;
	lineptr = NULL;
	stream = fopen(info->args[1], "r");

	if (stream == NULL)
	{
		fprintf(stderr, "Error: Can't open file: %s\n", info->args[1]);
		exit(EXIT_FAILURE);
	}

	while (getLine(&lineptr, &n, stream) != -1)
	{
		info->command = tokenize(lineptr, delim);
		info->line = line;

		if (info->command != NULL)
			runCommand(info);

		free(lineptr);
		lineptr = NULL;
		line++;
	}
	return (0);
}

/**
 * runCommand - runs the monty command passed in
 *
 * @info: a struct containing all the needed info
 *
 * Return: -1 on failure and 0 on success
 */

int runCommand(info_t *info)
{
	int i;
	instruction_t commands[] = {
		{"push", &push},
		{"pall", &pall},
		{NULL}
	};

	for (i = 0; commands[i].opcode != NULL; i++)
	{
		if (strcmp(info->command[0], commands[i].opcode) == 0)
		{
			commands[i].f(&(info->programStack), info->line);
			return (0);
		}
	}
	fprintf(stderr, "L%d: unknown instruction <opcode>", info->line);
	return (-1);
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
	while (current->next != NULL)
		current = current->next;
	new->prev = current;
	current->next = new;
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
		fprintf(stderr, "Error: L%u\n", line_number);

	if (*stack == NULL)
		return;

	current = *stack;

	while (current->next != NULL)
		current = current->next;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
}

/**
 * getLine - this function reads and saves the specified length
 * of characters in the provided pointer location
 *
 *@lineptr: an array of string
 *@bufferSize: the length of characters to read
 *@stream: the file stream to read from
 *
 * Return: returns -1 on failure to read a line or EOF else it returns
 * the number of characters read
 */

int getLine(char **lineptr, size_t *bufferSize, FILE *stream)
{
	size_t i = 0;
	int c;

	if (!(*lineptr))
	{
		*bufferSize = 1024;
		*lineptr = malloc(*bufferSize * sizeof(char));

		if (!(*lineptr))
		{
			perror("Memory reallocation error");
			exit(EXIT_FAILURE);
		}
	}
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i == *bufferSize - 1)
		{
			*bufferSize *= 1.5;
			*lineptr = realloc(*lineptr, *bufferSize * sizeof(char));
			if (!(*lineptr))
			{
				perror("Memory reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[i] = c;
		i++;
	}

	if (i == 0 && c == EOF)
	{
		return (-1);
	}
	*bufferSize = i + 3;
	*lineptr = realloc(*lineptr, *bufferSize * sizeof(char));
	(*lineptr)[i] = '\0';
	return (i);
}
