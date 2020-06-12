stack_client: stack_client.o stack.o
	gcc -Wall -o stack_client stack_client.o stack.o

stack_client.o: stack_client.c stack.h
	gcc -Wall -c stack_client.c

stack.o: stack.c stack.h
	gcc -Wall -c stack.c
