CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic -Wno-format-truncation -fsanitize=undefined

all: main.c arithmetic.c
	$(CXX) $(CXX_WARN) main.c arithmetic.c

clean:
	rm -f *.out