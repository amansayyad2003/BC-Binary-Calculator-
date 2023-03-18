#include "stack_num.h"
#include <stdlib.h>
//#include <stdio.h>

void init_stack_num(stack_num *n){
		(*n) = NULL;
		return;
}

int isEmpty_stack_num(stack_num *n){
		return (*n) == NULL;
}

void push_num(stack_num *n, head number){
		node_num *temp;
		temp = (*n);
		(*n) = (node_num*)malloc(sizeof(node_num));
		(*n)->number = number;
	   	(*n)->next = temp;
		return;
}	

head pop_num(stack_num *n){
		if(isEmpty_stack_num(n))
				return NULL;
		node_num *temp = (*n)->next;
		head h = (*n)->number;
		free(*n);
		(*n) = temp;
		return h;
}

head peek_num(stack_num *n){
		if(isEmpty_stack_num(n))
				return NULL;
		return (*n)->number;
}


/*int main(){
		stack_num s, s1;
		init_stack_num(&s);
		init_stack_num(&s1);
		head number, number1;
		init_head(&number);
		make_node_backward(&number->integer, 1);
		push_num(&s, number);
		number1 = pop_num(&s);
		printf("%d\n", number1->integer->value);
		return 0;
}*/
