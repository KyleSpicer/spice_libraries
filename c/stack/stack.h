#ifndef STACK_H
#define STACK_H

typedef struct stack_node_t stack_node_t;

struct stack_node_t
{
    int                   data;
    struct stack_node_t * next;
};

typedef struct stack_t stack_t;

stack_t * stack_create();

void stack_push(stack_t * stack, int data);

int is_stack_empty(stack_t * stack);

stack_node_t * stack_pop(stack_t * stack);

stack_node_t * stack_peek(stack_t * stack);

void stack_display(stack_t * stack);

void stack_destroy(stack_t ** stack);



#endif /* STACK_H */

/*** end of file ***/