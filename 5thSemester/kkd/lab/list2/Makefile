CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic -Wno-format-truncation

all: main.c arithmetic.c entropy.c
	$(CXX) $(CXX_WARN) main.c arithmetic.c entropy.c -lm

clean:
	rm -f *.out out*.test decoded*.test