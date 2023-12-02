all: main

main: main.o phi.o
	clang -o main main.o phi.o

main.o: main.c
	clang -Wextra -std=c11 --pedantic -c main.c

phi.o: phi.c
	clang -Wextra -std=c11 --pedantic -c phi.c

clean:
	rm -f main *.o *~
