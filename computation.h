#include "stack.h"
//#include <stdlib.h>
#include <stdbool.h>

typedef struct num{
		list integer;
		list float_num;
		int count;
		int sign;
}num;

typedef num *head;

void init_head(head *h);
void make_node_backward(list *node1, int value);
void make_node_forward(list *node1, int value);
void insert(head h, int value, bool point);
int big(head h1, head h2);
void reverse(head h);		
head substract(head h1, head h2);
head multi(head h1, int num);
int add_elements_to_stack(list l, stack *s);
int isZero(head h);
int power(int num, int raise);
head divide(head h2, head h1);
head addition(head h1, head h2);
head multiplication(head h1, head h2);
//void insert(head h, int value, bool point);
