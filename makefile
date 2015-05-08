
COMPFLAGS = -Wall -std=c99

all: enigma.o main.o
	gcc $(COMPFLAGS) main.o enigma.o -o enigma

enigma.o: enigma.h enigma.c
	gcc $(COMPFLAGS) -c enigma.c

main.o: enigma.h main.c
	gcc $(COMPFLAGS) -c main.c