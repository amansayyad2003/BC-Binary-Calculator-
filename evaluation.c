#include <stdio.h>
#include "evaluation.h"

void reverse_stak_num(stack_num *s){
		stack_num temp;
		init_stack_num(&temp);
		while(!isEmpty_stack_num(s))
				push_num(&temp, pop_num(s));
		(*s) = temp;
		return;
}

int count_node(list l){
		int count= 0;
		while(l){
				count++;
				l = l->next;
		}
		return count;
}

void evaluation(stack_num *s){
		stack_num intermediate;
		head num; 
		list l;
		init_stack_num(&intermediate);
		init_head(&num);
		while(!isEmpty_stack_num(s)){
				num = pop_num(s);
				if(num->integer->value == '+'){
						push_num(&intermediate, addition(pop_num(&intermediate), pop_num(&intermediate)));
						head h;
						init_head(&h);
						h = peek_num(&intermediate);
						l = h->integer;
						while(l){
							l = l->next;
						}
				}
				else if(num->integer->value == '-'){

						push_num(&intermediate, substract(pop_num(&intermediate), pop_num(&intermediate)));
				}
				else if(num->integer->value == '*'){
						push_num(&intermediate, multiplication(pop_num(&intermediate), pop_num(&intermediate)));
				}
				else if(num->integer->value == '/'){
						push_num(&intermediate, divide(pop_num(&intermediate), pop_num(&intermediate)));
				}
				else{
						push_num(&intermediate, num);
				}
		}
		reverse(intermediate->number);
		l = intermediate->number->integer;
		int count = count_node(l);
		printf("Result: ");
		if(intermediate->number->sign == -1)
					printf("-");
		while(l){
				if(intermediate->number->count > 0 && intermediate->number->count == count )
						printf(".");
				printf("%d", l->value);
				l = l->next;
				count--;
		}
		printf("\n");
		return;
}
