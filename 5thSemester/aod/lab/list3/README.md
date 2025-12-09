# Shortest Path Finding
## By Michał Waluś.

Made in C++23, uses only the standard library.

## Compilation

Compile using 
```sh
$ make
```

Run the program as 
```sh
$ ./app.out [algorithm] -d [graph] -ss [sources] -oss [output] 
$ # or
$ ./app.out [algorithm] -d [graph] -p2p [pairs] -oss [output]
```

Running with `-ss` means we want to find the shortest paths to all vertices from given sources, while running with `-p2p` finds lengths of the shortest path between given pairs of vertices.

Available algorithms are: dijkstra, dial and radix (radixheap).

## File formats

Files should have following structure:
- File specifying the graph:
```
c lines starting with c are comments
c
p sp 1024 3936
c lines starting with p specify problem type
c sp means the shortest path problem
c first number after sp is the number of vertices
c and the second one is the number of edges
c
c lines with a specify arcs (edges) and have structure
c "a [from] [to] [weight]"
a 853 274 591
a 853 565 867
a 274 853 29
```
- Files specifying sources
```
c lines that start with c are still comments
c
p aux sp ss 5
c the last number specifies the number of sources
c
c "s [vertex]" defines a source
s 17
s 124
s 13
s 1
s 1000
```

- Files specifying pairs
```f inputs/Long-C/Long-C.0.0.gr inputs/Long-C/Long-C.ss

c comment
p aux sp p2p 3
c the number specifies how many pairs there are
c "q [from] [to]" defines the path we want to find
c
q 123 122
q 1 1024
q 17 467
```

- Output files for ss
```
c comment
p res sp ss dijkstra
c last argument in p is the used algorithm
c f line specifies files that were given
f inputs/Long-C/Long-C.0.0.gr inputs/Long-C/Long-C.ss
c
c g line specify parameters of the graph
c "g [vertices] [arcs] [minweight] [maxweight]"
g 1024 3936 0 1024
c 
c t lines specify the average time of finding all paths
c from a single sources, given in ms
t 213.7
```

- Output files for p2p
```
c c, f, g and t lines same as above
c p lines are similar, with "ss" changed to "p2p"
p res sp p2p dijkstra
f inputs/Long-C/Long-C.0.0.gr inputs/Long-C/Long-C.p2p
g 1024 3936 0 1024
t 123
c
c lines starting with q give results for each path
c "q [from] [to] [length]"
q 123 122 17
q 1 1024 14576
q 17 467 2417
```

## Project structure

Code implementations is contained in include/ and src/ directories, and main.cpp file is in app/.

- dijkstra.* - files implementing the three algorithms: Dijkstra, Dial and RadixHeap.
- filemanager.* - files with code responsible for parsing input files.
- graph.* - files specifying graph class used in algorithms. 