all: main

main: main.o rozwiazanie.o f.o
	clang -o main main.o rozwiazanie.o f.o -lm

main.o: main.c
	clang -Wextra -std=c11 --pedantic -c main.c

rozwiazanie.o: rozwiazanie.c
	clang -Wextra -std=c11 --pedantic -c rozwiazanie.c 

f.o: f.c
	clang -Wextra -std=c11 --pedantic -c f.c

clean:
	rm -f main *.o *~