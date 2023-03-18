#include <stdlib.h>

typedef struct node{
		char value;
		struct node *next;
}node;

typedef node *stack, *list;

void init(stack *s);

int isEmpty(stack *s);

int peek(stack *s);

void push(int value, stack *s);

int pop(stack *s);



		
