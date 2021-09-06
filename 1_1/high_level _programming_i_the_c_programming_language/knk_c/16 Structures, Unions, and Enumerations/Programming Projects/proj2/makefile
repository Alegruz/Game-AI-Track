inventory: inventory.o quicksort.o readline.o
	gcc -o inventory inventory.o quicksort.o readline.o

inventory.o: inventory.c inventory.h quicksort.h readline.h
	gcc -c inventory.c

quicksort.o: quicksort.c quicksort.h inventory.h
	gcc -c quicksort.c

readline.o: readline.c readline.h
	gcc -c readline.c
