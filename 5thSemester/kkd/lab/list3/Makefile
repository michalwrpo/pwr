CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic -Wno-format-truncation

all: main.c elias.c fibonacci_coding.c lzw.c entropy.c
	$(CXX) $(CXX_WARN) main.c elias.c fibonacci_coding.c lzw.c entropy.c -lm

clean:
	rm -f *.out