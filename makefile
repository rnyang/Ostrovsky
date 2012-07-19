CFLAGS=
CC=g++

all: main

main:
	$(CC) $(CFLAGS) main.cpp main.h -o main

clean:
	rm -f main *# *~