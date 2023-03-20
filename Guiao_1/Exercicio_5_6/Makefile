CC = gcc
CFLAGS = -Wall -g

allprog: Person main
	$(CC) $(CFLAGS) person.o main.o -o person

debug: CFLAGS += -g -O0
debug: allprog

Person: person.c person.h
	$(CC) $(CFLAGS) -o person.o -c person.c 

main: person.o
	$(CC) $(CFLAGS) -o main.o -c main.c

clean: 
	@echo -n "Cleaning...\n"
	rm *.o
	rm person
