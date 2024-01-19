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
		fprintf(stderr, "Error: Can't open file %s\n", info->args[1]);
		freeStack();
		exit(EXIT_FAILURE);
	}

	info->currentStream = stream;
	while (getLine(&lineptr, &n, stream) != -1)
	{
		info->command = tokenize(lineptr, delim);
		info->line = line;

		if (info->command != NULL)
		{
			addMem(lineptr);
			runCommand(info);
			free(info->command);
			info->command = NULL;
		}
		else
			free(lineptr);

		lineptr = NULL;
		n = 0;
		line++;
	}
	if (lineptr != NULL)
		free(lineptr);
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
		{"pint", &pint},
		{"pop", &pop},
		{"swap", &swap},
		{"add", &arit},
		{"sub", &arit},
		{"div", &arit},
		{"mul", &arit},
		{"mod", &arit},
		{NULL}
	};

	for (i = 0; commands[i].opcode != NULL; i++)
	{
		if (strcmp(info->command[0], "nop") == 0)
			return (0);
		else if (strcmp(info->command[0], commands[i].opcode) == 0)
		{
			commands[i].f(&(info->programStack), info->line);
			return (0);
		}
	}
	fprintf(stderr, "L%d: unknown instruction %s\n",
			info->line, info->command[0]);
	freeStack();
	exit(EXIT_FAILURE);
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

	if ((*lineptr) == NULL)
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

/**
 * addMem - adds an address to the list of dynamically allocated memory
 *
 * @ptr: the address to add to the list
 */

void addMem(void *ptr)
{
	allocated_t *temp, *current;

	temp = malloc(sizeof(allocated_t));
	temp->address = ptr;
	temp->next = NULL;

	if (info->allocatedMem == NULL)
	{
		info->allocatedMem = temp;
		return;
	}

	current = info->allocatedMem;
	while (current->next != NULL)
		current = current->next;

	current->next = temp;

}

/**
 * freeMem - frees all dynamically allocated memory
 */

void freeMem(void)
{
	allocated_t *current, *temp;

	if (info->currentStream != NULL)
		fclose(info->currentStream);
	if (info->allocatedMem == NULL)
		return;

	current = info->allocatedMem;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->address);
		free(temp);
	}
}
