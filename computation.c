//#include "postfix.h"
#include <stdbool.h>
//#include <stdio.h>
#include "computation.h"

typedef num *head;

void init_head(head *h){
		*h = (num*)malloc(sizeof(num));
		(*h)->integer = NULL;
		(*h)->float_num = NULL;
		(*h)->count = 0;
}

void make_node_forward(list *node1, int value){
		list *temp = node1;
		while(*temp)
				temp = &((*temp)->next);
		(*temp) = (node*)malloc(sizeof(node));
		(*temp)->value = value;
		(*temp)->next = NULL;
		return;
}

void make_node_backward(list *node1, int value){
		list temp = *node1;
		(*node1) = (node*)malloc(sizeof(node));
		(*node1)->value = value;
		(*node1)->next = temp;
		return;
}

int big(head h1, head h2){
		stack s1, s2;
		list l1, l2;
		int count1, count2;
		init(&s1);
		init(&s2);
		l1 = h1->integer;
		l2 = h2->integer;
		count1 = count2 = 0;
		while(l1){
				push(l1->value, &s1);
				count1++;
				l1 = l1->next;
		}
		while(l2){
				push(l2->value, &s2);
				count2++;
				l2 = l2->next;
		}
		while(peek(&s1) == 0){
				pop(&s1);
				count1--;
		}
		while(peek(&s2) == 0){
				pop(&s2);
				count2--;
		}
		if((count1 - h1->count) > (count2 - h2->count)){
				return 1;
		}
		else if((count1 - h1->count) < (count2 - h2->count))
				return -1;
		while(!isEmpty(&s1) && !isEmpty(&s2)){
				count1 = pop(&s1);
				count2 = pop(&s2);
				if(count1 > count2)
						return 1;
				else if(count1 < count2){
						return -1;
				}
		}
		while(peek(&s1) == 0)
				pop(&s1);
		while(pop(&s2) == 0)
				pop(&s2);
		if((isEmpty(&s1) && isEmpty(&s2)))
				return 0;
		else if(!isEmpty(&s1))
				return 1;
		else
				return -1;
}

void reverse(head h){		
		list l;
		l = h->integer;
		stack s;
		init(&s);
		while(l){
				push(l->value, &s);
				l = l->next;
		}
		while(h->integer){
				l = h->integer->next;
				free(h->integer);
				h->integer = l;
		}
		while(!isEmpty(&s)) {make_node_forward(&h->integer, pop(&s));}
		return;
}


head substract(head h1, head h2){
		head result;
		list l1, l2;
		int num, count = 0, count1, count2;
		init_head(&result);

		count1 = h1->count;
		count2 = h2->count;
		if(count1 > count2){
				for(int i = 0; i < count1 - count2; i++){
						make_node_backward(&h2->integer, 0);
						h2->count++;
				}
				result->count = h1->count;
		}
		else{
				for(int i = 0; i < count2-count1; i++){
						make_node_backward(&h1->integer, 0);
						h1->count++;
				}
				result->count = h2->count;
		}
		num = big(h1, h2);
		if(num == 1){
				l1 = h1->integer;
				l2 = h2->integer;
				result->sign = 1;
		}
		else if(num == -1){
				l1 = h2->integer;
				l2 = h1->integer;
				result->sign = -1;
		}
		else{
				make_node_backward(&result->integer, 0);
				return result;
		}
		while(l1 && l2){
				num = l1->value;
				if(count != 0){
						num = num - 1;
						count = 0;
				}
				num = num - l2->value;
				if(num < 0){
						num = num + 10;
						count++;
				}
				make_node_backward(&result->integer, num);
				l1 = l1->next;
				l2 = l2->next;
		}
		while(l1){
				num = l1->value;
				if(count != 0){
						num = num - 1;
						count = 0;
				}
				if(num < 0){
						num = num + 10;
						count++;
				}
				make_node_backward(&result->integer, num);
				l1 = l1->next;
		}
		while(l2){
				num = l2->value;
				if(count != 0){
						num = num - 1;
						count = 0;
				}
				if(num < 0){
						num = num + 10;
						count++;
				}
				make_node_backward(&result->integer, num);
				l2 = l2->next;
		}

		while(result->integer->value == 0){
				l1 = result->integer->next;
				free(result->integer);
				result->integer = l1;
		}
		
		reverse(result);
		if(count1 > count2){
				for(int i = 0; i < count1 - count2; i++){
						l2 = h2->integer->next;
						free(h2->integer);
						h2->integer = l2;
						h2->count--;
				}
		}
		else{
				for(int i = 0; i < count2 - count1; i++){
						l1 = h1->integer->next; 
						free(h1->integer);
						h1->integer = l1;
						h1->count--;
				}
		}
		return result;
}

head multi(head h1, int num){
		head result;
		init_head(&result);
		list l = h1->integer;
		int num1, carry = 0;
		while(l){
				num1 = l->value*num + carry;
				make_node_forward(&result->integer, num1 % 10);
				carry = num1 / 10;
				l = l->next;
		}
		if(carry != 0)
				make_node_forward(&result->integer, carry);
		result->sign = h1->sign;
		result->count = h1->count;
		return result;
}

int add_elements_to_stack(list l, stack *s){
		int count = 0;
		while(l){
				push(l->value, s);
				count++;
				l = l->next;
		}
		return count;
}
		
int isZero(head h){
		list temp;
		temp = h->integer;
		while(temp){
				if(temp->value != 0)
						return 0;
				else
						temp = temp->next;
		}
		return 1;
}

int power(int num, int raise){
		if(raise == 1)
				return num;
		return num * power(num, raise - 1);
}

head divide(head h2, head h1){
		if(isZero(h1) || isZero(h2))
				return NULL;
		int num = 1, num1, count = 0;
		stack s;
		init(&s);
		head result, temp, h3;
		init_head(&result);
		init_head(&h3);
		init_head(&temp);
		add_elements_to_stack(h2->integer, &s);
		make_node_backward(&h3->integer, pop(&s));
		num1 = h1->count;
		h1->count = 0;

		temp = substract(h3, h1);
		while(temp->sign == -1 && !isEmpty(&s)){
				make_node_backward(&h3->integer, pop(&s));
				temp = substract(h3, h1);
		}
		while(!isEmpty(&s)){
				temp = substract(h3, h1);
				while(temp->sign == -1 && !isEmpty(&s)){
						make_node_backward(&h3->integer, pop(&s));
						temp = substract(h3, h1);
						if(count != 0){
								make_node_backward(&result->integer, 0);
						}
						count++;
				}
				count = 0;
				if(isEmpty(&s))
						break;
				temp = substract(h1, h3);
				while(temp->sign != 1){
						temp = multi(h1, ++num);
						temp = substract(temp, h3);
						
				}
				temp = multi(h1, --num);
				h3 = substract(h3, temp);
				make_node_backward(&result->integer, num);
				num = 1;
		}
		if(isZero(h3))
				return result;
		while(!isZero(h3) && result->count < 5){
				temp = substract(h3, h1);
				while(temp->sign == -1 && result->count < 5){
						result->count++;
						make_node_backward(&h3->integer, 0);
						temp = substract(h3, h1);
						if(count != 0){
								make_node_backward(&result->integer, 0);
						}
						count++;
				}
				temp = substract(h1, h3);
				while(temp->sign != 1){
						temp = multi(h1, ++num);
						temp = substract(temp, h3);
				}
				temp = multi(h1, --num);
				h3 = substract(h3, temp);
				make_node_backward(&result->integer, num);
				num = 1;
				count = 0;
		}
		h1->count = num1;

		for(int i = 0; i < h1->count; i++)
				result->count--;
		return result;

}

//head addition(head num1, head num2){
//		head sum_num;
//		init_head(&sum_num);
////		make_node_backward(&sum_num->integer, 0);
////		make_node_backward(&sum_num->float_num, 0);
//		list l1, l2, *sum;
//		int carry = 0, num;
//		int count = 0;
//		for(l1 = num1->float_num, l2 = num2->float_num, sum = &(sum_num->float_num); count <= 1; l1 = num1->integer, l2 = num2->integer, sum = &(sum_num->integer))

head addition(head h1, head h2){
		head sum_num;
		init_head(&sum_num);
		list l1, l2;
		l1 = h1->integer;
		l2 = h2->integer;
		int carry = 0, num;
		if(h1->count > h2->count){
				sum_num->count = h1->count;
				for(int i = 0; i < (h1->count - h2->count); i++){
						make_node_forward(&(sum_num->integer), l1->value);
						l1 = l1->next;
				}
		}
		else{
				sum_num->count = h2->count;
				for(int i = 0; i < (h2->count - h1->count); i++){
						make_node_forward(&(sum_num->integer), l2->value);
						l2 = l2->next;
				}
		}
		while(l1 && l2){
				num = l1->value + l2->value + carry;
				make_node_forward(&(sum_num->integer), num % 10);
				carry = num / 10;
				l1 = l1->next;
				l2 = l2->next;
		}
		while(l1){
				num = l1->value + carry;
				make_node_forward(&(sum_num->integer), num % 10);
				carry = num / 10;
				l1 = l1->next;
		}
		while(l2){
				num = l2->value + carry;
				make_node_forward(&(sum_num->integer), num % 10);
				carry = num / 10;
				l2 = l2->next;
		}
		if(carry != 0)
				make_node_forward(&(sum_num->integer), carry);

		return sum_num;
}


head multiplication(head h1, head h2){
		head result, h3, h4;
		list l;
		int count = 0;
		init_head(&result);
		init_head(&h3);
		init_head(&h4);

		if(isZero(h1) || isZero(h2)){
				make_node_backward(&result->integer, 0);
				return result;
		}
		l = h2->integer;
		h3 = multi(h1, l->value);
		l = l->next;
		count++;

		while(l){
				h4 = multi(h1, l->value);
				for(int i = 0; i < count; i++){
						make_node_backward(&h4->integer, 0);
				}
				h3 = addition(h3, h4);
				l = l->next;
				count++;
		}
		result = h3;
		result->count = h1->count + h2->count;
		
		count = 2;

		for(int i = 0; i < count; i++){
			reverse(result);
			while(result->integer->next != NULL && result->integer->value == 0 && result->count > 0){
					l = result->integer->next;
					free(result->integer);
					result->integer = l;
					if(i != 0){
							result->count--;
					}
			}
		}
		return result;
}

void insert(head h, int value, bool point){
		make_node_backward(&h->integer, value);
		if(point)
				h->count++;
		return;
}

/*  int main(){
  //		list l1 = NULL, l2 = NULL, l3 = NULL;
  //		printf("Enter first numberber: ");
  //		input_num(&l1);
  //		printf("Enter second number: ");
  //		input_num(&l2);
  //		l3 = addition(l1, l2);
  //		while(l3){
  //				printf("%d", l3->value);
  //				l3 = l3->next;
  //		}
  
  		char str1[10000];
  		scanf("%s", str1);
  
  		char str2[10000];
  		scanf("%s", str2);
  		
  		head number1;
		init_head(&number1);
  		head number2;
		init_head(&number2);
  		int index = 0;
 		precedence token;
		if((token = get_token(str1, &index)) == operand){
				insert(number1, str1[index - 1] - '0', false);
				while((token = get_token(str1, &index)) == operand){
						insert(number1, str1[index - 1] - '0', false);
				}
				if(token == point){
						while((token = get_token(str1, &index)) == operand){
								insert(number1, str1[index - 1] - '0', true);
						}
				}
		}

		int index1 = 0;
		if((token = get_token(str2, &index1)) == operand){
				//head number2 = NULL;
				insert(number2, str2[index1 - 1] - '0', false);
				while((token = get_token(str2, &index1)) == operand){
						insert(number2, str2[index1 - 1] - '0', false);
				}
				if(token == point){
						while((token = get_token(str2, &index1)) == operand){
								insert(number2, str2[index1 - 1] - '0', true);
						}
				}
		}
		
//		head number3, number4;
//		init_head(&number3);
//		init_head(&number4);
		
		head number;
	//	number = substract(number1, number2);
		number = multiplication(number1, number2);
		//int num;
		//num = big(number1, number2);
		//printf("%d", num);
		list l;
		l = number->integer;
		while(l){
				printf("%d",l->value);
				l = l->next;	
		}
		printf("\ncount: %d\n", number->count);
		printf("sign: %d\n", number->sign);
		//printf("\nsign = %d\n", number->sign);
		//printf("%d\n", number->count);
		//printf("\n");

//		list l1 = multi(number1, 2);
//		while(l1){
//				printf("%d",l1->value);
//				l1 = l1->next;	
//		}
			
//		int numm = big(number1, number2);
//		printf("%d\n", numm);
//		stack s;
//		init(&s);
//		add_elements_to_stack(&s, number2->integer);
//		while(s){
//				printf("%d",s->value);
//				s = s->next;	
//		}
		
		//int n = power(10, 5);
		//printf("%d\n", n);
		return 0;
}*/

			
				
				

