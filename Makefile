make: computation.o evaluation.o stack.o stack_num.o
	gcc main.c computation.o evaluation.o stack_num.o stack.o -o bc

computatation.o: computation.c 
	gcc -c computation.c 

evaluation.o: evaluation.c
	gcc -c evaluation.c

stack.o: stack.c
	gcc -c stack.c

stack_num.o: stack_num.o
	gcc -c stack_num.c

clean: 
	rm *.o	
	


