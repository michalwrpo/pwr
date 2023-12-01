all: main

main: main.o palindrom.o
	clang -o main main.o palindrom.o

main.o: main.c 
	clang -c main.c

palindrom.o: palindrom.c 
	clang -c palindrom.c

clean:
	rm -f main *.o *~