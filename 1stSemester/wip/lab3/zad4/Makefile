all: main

main: main.o newagent.o north.o south.o east.o west.o distance.o
	clang -o main main.o newagent.o north.o south.o east.o west.o distance.o -lm

main.o: main.c
	clang -Wextra -std=c11 --pedantic -c main.c

newagent.o: newagent.c
	clang -Wextra -std=c11 --pedantic -c newagent.c 

north.o: north.c 
	clang -Wextra -std=c11 --pedantic -c north.c 

south.o: south.c
	clang -Wextra -std=c11 --pedantic -c south.c 

east.o: east.c 
	clang -Wextra -std=c11 --pedantic -c east.c 

west.o: west.c 
	clang -Wextra -std=c11 --pedantic -c west.c 

distance.o: distance.c
	clang -Wextra -std=c11 --pedantic -c distance.c 

clean:
	rm -f main *.o *~