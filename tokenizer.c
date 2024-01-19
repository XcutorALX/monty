#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
#include <string.h>

/**
 * tokenize - a function that splits a string
 * into an array of string according to a delim provided
 *
 *@str: the string to be parsed
 *@delim: the delimeter to look out for
 *
 *Return: returns an array of strings
 */

char **tokenize(char *str, char *delim)
{
	size_t count, size;
	char **split, *buffer;

	size = 1024;
	split = malloc(size * sizeof(char *));
	if (!split)
		exit(EXIT_FAILURE);
	split[0] = strtok(str, delim);
	if (split[0] == NULL)
	{
		free(split);
		return (NULL);
	}
	for (count = 1; (buffer = strtok(NULL, delim)) != NULL
			&& *buffer != '\0'; count++)
	{
		if (count == size - 1)
		{
			size *= 1.5;
			split = realloc(split, size * sizeof(char *));
			if (!split)
				exit(EXIT_FAILURE);
		}
		split[count] = buffer;
	}
	split[count++] = NULL;
	size = count + 1;
	split = realloc(split, size * sizeof(char *));
	if (!split)
		exit(EXIT_FAILURE);
	return (split);
}
