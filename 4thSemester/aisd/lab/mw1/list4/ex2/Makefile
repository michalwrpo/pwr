CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic
CXX_FLAGS := -O3

bst:
	$(CXX) $(CXX_WARN) $(CXX_FLAGS) main.c bst.c mtwister.c -o app.out

clean:
	rm -f *.out