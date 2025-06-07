CXX := gcc
CXX_WARN := -Wall -Wextra -Werror -Wpedantic 

prim:
	$(CXX) $(CXX_WARN) prim.c graph.c mtwister.c -o prim.out

kruskal:
	$(CXX) $(CXX_WARN) kruskal.c graph.c mtwister.c -o kruskal.out

clean:
	rm -f *.out