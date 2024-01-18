#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct allocated_s - a linked list to keep track of allocated memory
 *
 * @address: the memory address
 * @next: a pointer to the next node
 *
 * Description: keeps track of allocated memory
 */

typedef struct allocated_s
{
	void *address;
	struct allocated_s *next;
} allocated_t;

/**
 * struct info_s - a linked list that contains all the needed info
 *
 * @command: the current command waiting to be executed
 * @programQueue: current program queue
 * @programStack: current program stack
 * @allocatedMem:  all dynamically allocated memory not freed yet
 * @line: the current line being executed
 * @errorno: tracks the errors in the program
 * @args: the command line arguments
 *
 * Description: contains all the needed info for the program to run
 */

typedef struct info_s
{
	char **command;
	char **args;
	stack_t *programStack;
	stack_t *programQueue;
	allocated_t *allocatedMem;
	int errorno;
	unsigned int line;
} info_t;

extern info_t *info;

void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
int runCommand(info_t *info);
int readCode(info_t *info);
int getLine(char **lineptr, size_t *buffersize, FILE *stream);
char **tokenize(char *str, char *delim);
int _atoi(char *str);
int _pow(long int x, long int y);
void freeStack(void);

#endif
