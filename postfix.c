#include <stdio.h>
#include "postfix.h"
#include "stack.h"
#include <stdlib.h>


int isp[] = {0, 20, 13, 13, 13, 12, 12, 0};
int icp[] = {20, 20, 13, 13, 13, 12, 12, 0};

int get_token(char *expr, int *index){
		char token = expr[(*index)++];
		switch(token){
				case '(': return lparen;
				case ')': return rparen;
				case '*': return mult;
				case '/': return division;
				case '%': return mod;
				case '+': return add;
				case '-': return sub;
				case '.': return point;
				case '\0': return eos;
				default : return operand;
		}
}

char *postfix(char *expr, int size){
		int index = 0, count = 0;
		char *pfix = (char*)malloc(sizeof(char)*size);
		precedence token;
		stack temps;
		init(&temps);
		for(token = get_token(expr, &index); token != eos; token = get_token(expr, &index)){
				if(token == operand)
					//	push(expr[index - 1] - '0', pstack);
						pfix[count++] = expr[index - 1];
				else if(token == rparen){
						while((token = pop(&temps)) != lparen )
						//		push(token, pstack);
								pfix[count++] = token;
						pop(&temps);    // lparen will get pop
				}
				else{
						if(!isEmpty(&temps)){
							while(isp[peek(&temps)] >= icp[token])
					//				push(pop(&temps), pstack);
									pfix[count++] = pop(&temps);
						}
						push(token, &temps);
						
				}  
		} 
		while(!isEmpty(&temps))
		//		push(pop(&temps), pstack);
				pfix[count++] = pop(&temps);
		pfix[count] = eos;
		return pfix;
}

int eval(char *pfix){
		int oper1, oper2, index = 0;
		stack s;
		init(&s);
		while(pfix[index] != eos){
			if(pfix[index] == operand){
				push(pfix[index] - '0', &s);	
				printf("*%d\n", pfix[index] - '0');
			}
			else{
					oper2 = pop(&s); 
					oper1 = pop(&s); 
					switch(pfix[index]){
							case mult:
									push(oper1 * oper2, &s);
									break;
							case division:  
									push(oper1 / oper2, &s);
									break;
							case mod:
									push(oper1 % oper2, &s);
									break;
							case add:
									push(oper1 + oper2, &s);
									break;
							case sub:
									push(oper1 + oper2, &s);
									break;
					}
			}
			index++;
		}
		return pop(&s);
}

 
			
/* int main(){
		char expr[] = "1+2*(4/2+1)";
		char *a = postfix(expr, sizeof(expr));
		int num = eval(a);
		printf("%d\n", num);	
		return 0;
} */
