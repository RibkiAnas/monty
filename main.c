#include "monty.h"
#include <stdio.h>

/**
 * main - entry point for monty
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	FILE *fp;
	char line[BUFSIZE], *opcode;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	instruction_t opcodes[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop},
		{"swap", swap}, {"add", add}, {NULL, NULL}
	};
	int i;

	fp = fopen(argv[1], "r");
	if (argc != 2 || !fp)
	{
		fprintf(stderr, argc != 2 ? USAGE : "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	while (fgets(line, BUFSIZE, fp))
	{
		line_number++;
		opcode = strtok(line, DELIMS);
		if (opcode == NULL || *opcode == '#')
			continue;
		for (i = 0; opcodes[i].opcode; i++)
			if (strcmp(opcode, opcodes[i].opcode) == 0)
				break;
		if (opcodes[i].opcode)
			opcodes[i].f(&stack, line_number);
		else
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
			free_stack(&stack);
			fclose(fp);
			return (EXIT_FAILURE);
		}
	}
	free_stack(&stack);
	fclose(fp);
	return (EXIT_SUCCESS);
}

/**
 * free_stack - frees a stack
 * @stack: double pointer to the top of the stack
 */
void free_stack(stack_t **stack)
{
	stack_t *tmp;

	while (*stack)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
}
