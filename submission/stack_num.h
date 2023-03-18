#include "computation.h"

typedef struct node_num{
		head number;
		struct node_num *next;
}node_num;

typedef node_num *stack_num, *list_stack;

void init_stack_num(stack_num *n);
int isEmpty_stack_num(stack_num *n);
void push_num(stack_num *n, head number);
head pop_num(stack_num *n);
head peek_num(stack_num *n);
