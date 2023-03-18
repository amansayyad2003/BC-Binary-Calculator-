//#include <stdlib.h>
//#include <stdio.h>
#include <limits.h> 
#include "stack.h"

void init(stack *s){
		*s = NULL; 
}

int isEmpty(stack *s){
		return *s == NULL;
}

int peek(stack *s){
		if(isEmpty(s))
				return INT_MIN;
		return (*s)->value;
}

void push(int value, stack *s){
		if(isEmpty(s)){
				*s = (node*)malloc(sizeof(node));
				(*s)->value = value;
				(*s)->next = NULL;
				return;
		}
		list temp = *s;
		*s = (node*)malloc(sizeof(node));
		(*s)->value = value;
		(*s)->next = temp;
		return;
}

int pop(stack *s){
		if(isEmpty(s))
				return INT_MIN;
		list temp = (*s)->next;
		int value = (*s)->value;
		free(*s);
		*s = temp;
		return value;
}

