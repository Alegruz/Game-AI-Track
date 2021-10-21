main: main.o cpu_scheduler.o queue.o process_control_block.o
	gcc -Wall -o main main.o cpu_scheduler.o queue.o process_control_block.o -g

main.o: main.c
	gcc -Wall -c main.c -g

cpu_scheduler.o: cpu_scheduler.c cpu_scheduler.h build_settings.h
	gcc -Wall -c cpu_scheduler.c -g

queue.o: queue.c queue.h build_settings.h
	gcc -Wall -c queue.c -g

process_control_block.o: process_control_block.c process_control_block.h build_settings.h
	gcc -Wall -c process_control_block.c -g