
COMPFLAGS = -Wall -std=c99

all: enigma.o test.o
	gcc $(COMPFLAGS) test.o enigma.o -o enigma

enigma.o: enigma.h enigma.c
	gcc $(COMPFLAGS) -c enigma.c

test.o: enigma.h test.c
	gcc $(COMPFLAGS) -c test.c