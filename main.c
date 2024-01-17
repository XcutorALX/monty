#include <stdio.h>
#include <stdlib.h>
#include "monty.h"

info_t *info;

/**
 * main - entry point
 *
 * @argc: the number of command line arguments passsed in
 * @argv: an array of command line arguments as strings
 *
 * Return: 0 on success and 1 on failure
 */

int main(int argc, char **argv)
{
	info_t progInfo;

	info = &progInfo;
	if (argc < 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
		return (-1);
	}

	info->command = NULL;
	info->args = argv;
	info->programStack = NULL;
	info->programQueue = NULL;
	info->allocatedMem = NULL;

	readCode(info);
	return (0);
}
