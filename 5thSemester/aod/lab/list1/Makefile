CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic 

ex1: ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c
	$(CXX) $(CXX_WARN) ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c -o ex1.out

ex2: ex2/main.c ex2/topological_sort.c ex2/graph.c
	$(CXX) $(CXX_WARN) ex2/main.c ex2/topological_sort.c ex2/graph.c -o ex2.out

ex3: ex3/main.c ex3/scc.c ex3/graph.c
	$(CXX) $(CXX_WARN) ex3/main.c ex3/scc.c ex3/graph.c -o ex3.out

clean:
	rm -f *.out