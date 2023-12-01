all: main

main: main.o palindrom.o
	clang -o main main.o palindrom.o

main.o: main.c 
	clang -Wextra -std=c11 --pedantic -c main.c

palindrom.o: palindrom.c 
	clang -Wextra -std=c11 --pedantic -c palindrom.c

clean:
	rm -f main *.o *~