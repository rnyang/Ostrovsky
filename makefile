CFLAGS=
CC=g++

all: ostrovsky.o

ostrovsky.o:
	$(CC) $(CFLAGS) ostrovsky.cpp ostrovsky.h utility.cpp utility.h -o ostrovsky

clean:
	rm -f ostrovsky *# *~ *.o