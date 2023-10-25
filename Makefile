CC=gcc
FLAGS=-Wall -lm

all: clean matrix.o
	$(CC) main.c matrix.o -o main $(FLags)

matrix.o:
	$(CC) matrix.c -c -o matrix.o $(FLAGS)

clean:
	rm -f *.o main
