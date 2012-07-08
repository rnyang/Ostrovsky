CFLAGS=-Wall -g

all: main

main:
	$(CC) $(CFLAGS) main.cpp -o main

clean:
	rm -f main