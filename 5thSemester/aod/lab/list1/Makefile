CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic -Wno-format-truncation

ex1: ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c
	$(CXX) $(CXX_WARN) ex1/main.c ex1/bfs.c ex1/dfs.c ex1/graph.c -o ex1.out

ex2: ex2/main.c ex2/topological_sort.c ex2/graph.c
	$(CXX) $(CXX_WARN) ex2/main.c ex2/topological_sort.c ex2/graph.c -o ex2.out

ex3: ex3/main.c ex3/scc.c ex3/graph.c
	$(CXX) $(CXX_WARN) ex3/main.c ex3/scc.c ex3/graph.c -o ex3.out

ex4: ex4/main.c ex4/graph.c ex4/bipartite.c
	$(CXX) $(CXX_WARN) ex4/main.c ex4/graph.c ex4/bipartite.c -o ex4.out

clean:
	rm -f *.out