#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct stack_t {
	stack_node_t *topnode;
	int size;
};

stack_t *stack_create()
{
	stack_t *stack = calloc(1, sizeof(stack_t));
	stack->topnode = NULL;
	stack->size = 0;
	return stack;
}

void stack_push(stack_t * stack, int data)
{
	if (!stack || !data) {
		return;
	}
	stack_node_t *new_node = calloc(1, sizeof(stack_node_t));
	new_node->data = data;
	new_node->next = stack->topnode;
	stack->topnode = new_node;
	stack->size++;
}

int is_stack_empty(stack_t * stack)
{
	if (!stack) {
		return -1;
	}
	return stack->size == 0;
}

stack_node_t *stack_pop(stack_t * stack)
{
	if (!stack) {
		return NULL;
	} else if (is_stack_empty(stack)) {
		printf("Stack is empty!.\n");
		return NULL;
	}
	stack_node_t *temp = stack->topnode;
	stack->topnode = temp->next;
	stack->size--;
	return temp;
}

stack_node_t *stack_peek(stack_t * stack)
{
	if (!stack) {
		return NULL;
	} else if (is_stack_empty(stack)) {
		printf("Stack is empty!.\n");
		return NULL;
	}
	return stack->topnode;
}

void stack_display(stack_t * stack)
{
	if (!stack) {
		return;
	}

	stack_node_t *curr = stack->topnode;
	while (curr != NULL) {
		printf("%d ", curr->data);
		curr = curr->next;
	}
	printf("\n");
}

void stack_destroy(stack_t ** stack)
{
	if (!*stack || !stack) {
		return;
	}
	stack_node_t *curr = (*stack)->topnode;
	while (curr != NULL) {
		stack_node_t *next = curr->next;
		free(curr);
		curr = next;
	}

	free(*stack);
	stack = NULL;
}

/*** end of file ***/
