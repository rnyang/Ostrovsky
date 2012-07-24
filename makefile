CFLAGS=
CC=g++

all: main.o

main.o:
	$(CC) $(CFLAGS) main.cpp main.h -o main

clean:
	rm -f main *# *~ *.o