CC=gcc
FLAGS=-Wall -Wextra -lm -O3

all: clean matrix.o
	$(CC) main.c matrix.o -o main $(FLAGS)

matrix.o:
	$(CC) matrix.c -c -o matrix.o $(FLAGS)

clean:
	rm -f *.o main
