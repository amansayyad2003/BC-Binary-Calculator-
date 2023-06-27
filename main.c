#include <stdio.h>
#include "postfix/postfix.h"
//#include "stack_num.h"
#include "evaluation.h"

#define SIZE 1000000

/*void Display(stack_num postfix){
		list_stack temp;
		init_stack_num(&temp);
		temp = postfix;
		list a;
		while(temp){
				a = temp->number->integer;
				while(a){
						printf("%d", a->value);
						a = a->next;
				}
				printf("\t");
				temp = temp->next;
		}
		printf("\n");
}*/

/*void reverse_stak_num(stack_num *s){
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
}*/


int main(){
		printf("-> Simple BC which will give result of infix expression\n");
		printf("-> To know what this bc can do look at README_FILE\n\n");
		printf("!!!!!!	press CTRL_D to EXIT !!!!!!\n\n");
		char str1[SIZE];
		char a;
		int i = 0;
		head number1, number2;
		init_head(&number1);
		init_head(&number2);
		int index = 0, token;
		stack_num postfix, temp;
		init_stack_num(&postfix);
		init_stack_num(&temp);
		while(1){
				printf(">> ");
		while((a = getchar()) != '\n'){
				str1[i++] = a;
		}
		str1[i] = '\0';

		while(str1[index] != '\0'){
				if(str1[index] == ' '){
						index++;
						continue;
				}
				while((token = str1[index]) >= '0' && token <= '9'){
						insert(number1, str1[index++] - '0', false);
				}
				if(token == '.'){
						index++;
						while((token = str1[index]) >= '0' && token <= '9'){
								insert(number1, str1[index++] - '0', true);
						}
				}
				if(number1->integer != NULL)
						push_num(&postfix, number1);
				
				if(isEmpty_stack_num(&temp) && (token == '+' || token == '-' || token == '*' || token == '/' || token == '(' || token == ')'))
						insert(number2, str1[index++], false);
				else if(token == '(')
						insert(number2, str1[index++], false);
				else if(token == ')'){
						while(peek_num(&temp)->integer->value != '('){
								push_num(&postfix, pop_num(&temp));
						}
						index++;
						pop_num(&temp);
				}
				else if(token == '*'){
						while(!isEmpty_stack_num(&temp) && (peek_num(&temp)->integer->value == '/' || peek_num(&temp)->integer->value == '*')){
								push_num(&postfix, pop_num(&temp));
						}
						insert(number2, str1[index++], false);
				}
				else if(token == '/'){
						while(!isEmpty_stack_num(&temp) && (peek_num(&temp)->integer->value == '/' || peek_num(&temp)->integer->value == '*')){
								push_num(&postfix, pop_num(&temp));
						}
						insert(number2, str1[index++], false);
				}
				else if(token == '+'){
						while(!isEmpty_stack_num(&temp) && (peek_num(&temp)->integer->value == '/' || peek_num(&temp)->integer->value == '-' || peek_num(&temp)->integer->value == '*' || peek_num(&temp)->integer->value == '+')){
								push_num(&postfix, pop_num(&temp));
						}
						insert(number2, str1[index++], false);
				}
				else if(token == '-'){
						while(!isEmpty_stack_num(&temp) && (peek_num(&temp)->integer->value == '-' || peek_num(&temp)->integer->value == '*' || peek_num(&temp)->integer->value == '/')){
								push_num(&postfix, pop_num(&temp));
						}
						insert(number2, str1[index++], false);
				}
				if(number2->integer != NULL)	
						push_num(&temp, number2);
				init_head(&number1);
				init_head(&number2);
		}

		while(!isEmpty_stack_num(&temp)){
				push_num(&postfix, pop_num(&temp));
		}
		reverse_stak_num(&postfix);
		evaluation(&postfix);
		printf("\n");
}
		
		return 0;
}
	

