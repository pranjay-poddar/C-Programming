
output:main.o input.o future.o deck.o cards.o
	gcc -g main.o input.o future.o deck.o cards.o -o output
main.o:main.c
	gcc -c main.c
future.o:future.c future.h
	gcc -c future.c
input.o:input.c input.h
	gcc -c input.c
cards.o:cards.c cards.h
	gcc -c cards.c
deck.o:deck.c deck.h
	gcc -c deck.c
