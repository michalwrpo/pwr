all: main

main: main.o decode.o
	clang -o main main.o decode.o -lm

main.o: main.c
	clang -Wextra -std=c11 --pedantic -c main.c

decode.o: decode.c
	clang -Wextra -std=c11 --pedantic -c decode.c

clean: 
	rm -f main *.o *~