CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic 

ex1: ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c
	$(CXX) $(CXX_WARN) ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c -o ex1.out

clean:
	rm -f *.out