# List 1

## Ex. 1

```sh
[Michal@CrimsonNight list1]$ ./ex1.out bfs tree 
File: ./tests/1/d1-1.txt
1 2 3 4 5 6 
1
∟2
 ∟4
 ∟5
∟3
 ∟6
File: ./tests/1/d1-2.txt
1 2 4 3 6 8 5 7 
1
∟2
 ∟3
 ∟6
  ∟5
  ∟7
∟4
 ∟8
File: ./tests/1/d1-3.txt
1 2 3 5 4 6 8 7 9 
1
∟2
 ∟4
  ∟8
∟3
 ∟6
  ∟7
  ∟9
∟5
File: ./tests/1/d1-4.txt
1 2 5 7 3 10 6 8 4 11 9 
1
∟2
 ∟3
  ∟4
  ∟11
 ∟10
∟5
 ∟6
  ∟9
∟7
 ∟8
File: ./tests/1/u1-1.txt
1 2 3 4 5 6 
1
∟2
 ∟4
 ∟5
∟3
 ∟6
File: ./tests/1/u1-2.txt
1 2 4 5 3 6 8 7 
1
∟2
 ∟3
  ∟7
 ∟6
∟4
 ∟8
∟5
File: ./tests/1/u1-3.txt
1 2 3 5 4 6 7 8 9 
1
∟2
 ∟4
  ∟8
∟3
 ∟6
  ∟9
∟5
 ∟7
File: ./tests/1/u1-4.txt
1 2 5 7 3 10 6 8 4 11 9 
1
∟2
 ∟3
  ∟4
  ∟11
 ∟10
∟5
 ∟6
  ∟9
∟7
 ∟8
[Michal@CrimsonNight list1]$ ./ex1.out dfs tree 
File: ./tests/1/d1-1.txt
1 2 3 5 6 4 
1
∟2
 ∟3
  ∟5
   ∟6
 ∟4
File: ./tests/1/d1-2.txt
1 2 3 4 8 7 6 5 
1
∟2
 ∟3
  ∟4
   ∟8
    ∟7
 ∟6
  ∟5
File: ./tests/1/d1-3.txt
1 2 4 5 6 7 8 9 3 
1
∟2
 ∟4
  ∟5
   ∟6
    ∟7
     ∟8
    ∟9
∟3
File: ./tests/1/d1-4.txt
1 2 3 4 9 11 10 5 6 7 8 
1
∟2
 ∟3
  ∟4
   ∟9
  ∟11
 ∟10
∟5
 ∟6
∟7
 ∟8
File: ./tests/1/u1-1.txt
1 2 3 5 4 6 
1
∟2
 ∟3
  ∟5
   ∟4
   ∟6
File: ./tests/1/u1-2.txt
1 2 3 4 8 5 6 7 
1
∟2
 ∟3
  ∟4
   ∟8
    ∟5
     ∟6
      ∟7
File: ./tests/1/u1-3.txt
1 2 4 5 3 6 7 8 9 
1
∟2
 ∟4
  ∟5
   ∟3
    ∟6
     ∟7
      ∟8
       ∟9
File: ./tests/1/u1-4.txt
1 2 3 4 9 6 5 10 8 7 11 
1
∟2
 ∟3
  ∟4
   ∟9
    ∟6
     ∟5
      ∟10
    ∟8
     ∟7
     ∟11
```

## Ex. 2

```sh
File: g2a-1.txt
Graph does not have a directed cycle.
Topological order: 1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16 
File: g2a-2.txt
Graph does not have a directed cycle.
Topological order: 1 11 21 31 41 51 61 71 81 91 2 12 22 32 42 52 62 72 82 92 3 13 23 33 43 53 63 73 83 93 4 14 24 34 44 54 64 74 84 94 5 15 25 35 45 55 65 75 85 95 6 16 26 36 46 56 66 76 86 96 7 17 27 37 47 57 67 77 87 97 8 18 28 38 48 58 68 78 88 98 9 19 29 39 49 59 69 79 89 99 10 20 30 40 50 60 70 80 90 100 
File: g2a-3.txt
Graph does not have a directed cycle.
File: g2a-4.txt
Graph does not have a directed cycle.
File: g2a-5.txt
Graph does not have a directed cycle.
File: g2a-6.txt
Graph does not have a directed cycle.
File: g2a-7.txt
Graph does not have a directed cycle.
Topological order: 1 7 8 5 6 2 10 3 11 4 9 
File: g2b-1.txt
Graph has a directed cycle.
File: g2b-2.txt
Graph has a directed cycle.
File: g2b-3.txt
Graph has a directed cycle.
File: g2b-4.txt
Graph has a directed cycle.
File: g2b-5.txt
Graph has a directed cycle.
File: g2b-6.txt
Graph has a directed cycle.
File: g2b-7.txt
Graph have a directed cycle.
```

## Ex. 3

```sh
[Michal@CrimsonNight list1]$ ./ex3.out 
File: g3-1.txt
Number of strongly connected components: 5 (5, 4, 4, 2, 1) 
SCC 1: 1 2 3 4 5 
SCC 2: 12 15 14 13 
SCC 3: 6 8 9 7 
SCC 4: 10 11 
SCC 5: 16 
File: g3-2.txt
Number of strongly connected components: 5 (6, 40, 36, 24, 1) 
SCC 1: 1 2 3 4 5 6 
SCC 2: 67 106 105 104 103 102 101 100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 
SCC 3: 7 13 14 8 20 21 15 9 27 28 22 16 10 34 35 29 23 17 11 41 42 36 30 24 18 12 40 33 39 26 32 38 19 25 31 37 
SCC 4: 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 
SCC 5: 107 
File: g3-3.txt
Number of strongly connected components: 5 (7, 400, 400, 200, 1) 
File: g3-4.txt
Number of strongly connected components: 5 (8, 4000, 3600, 2400, 1) 
File: g3-5.txt
Number of strongly connected components: 5 (9, 40000, 40000, 20000, 1) 
File: g3-6.txt
Number of strongly connected components: 5 (10, 400000, 360000, 240000, 1) 
File: g3-7.txt
Number of strongly connected components: 3 (9, 1, 1) 
SCC 1: 1 9 4 3 2 6 5 8 7 
SCC 2: 10 
SCC 3: 11 
File: g3-8.txt
Number of strongly connected components: 5 (4, 2, 4, 1, 1) 
SCC 1: 1 4 2 3 
SCC 2: 5 6 
SCC 3: 7 10 9 8 
SCC 4: 11 
SCC 5: 12 
```

## Ex. 4

```sh
[Michal@CrimsonNight list1]$ ./ex4.out 
File: d4a-1.txt
The graph is bipartite.
V0: 1 3 6 8 9 11 14 16 
V1: 2 4 5 7 10 12 13 15 
File: d4a-2.txt
The graph is bipartite.
V0: 1 3 5 7 9 12 14 16 18 20 21 23 25 27 29 32 34 36 38 40 41 43 45 47 49 52 54 56 58 60 61 63 65 67 69 72 74 76 78 80 81 83 85 87 89 92 94 96 98 100 
V1: 2 4 6 8 10 11 13 15 17 19 22 24 26 28 30 31 33 35 37 39 42 44 46 48 50 51 53 55 57 59 62 64 66 68 70 71 73 75 77 79 82 84 86 88 90 91 93 95 97 99 
File: d4a-3.txt
The graph is bipartite.
File: d4a-4.txt
The graph is bipartite.
File: d4a-5.txt
The graph is bipartite.
File: d4a-6.txt
The graph is bipartite.
File: d4a-7.txt
The graph is bipartite.
V0: 1 3 5 7 9 
V1: 2 4 6 8 10 
File: d4b-1.txt
The graph is not bipartite.
File: d4b-2.txt
The graph is not bipartite.
File: d4b-3.txt
The graph is not bipartite.
File: u4b-4.txt
The graph is not bipartite.
File: d4b-5.txt
The graph is not bipartite.
File: u4b-6.txt
The graph is not bipartite.
File: d4b-7.txt
The graph is not bipartite.
File: u4a-1.txt
The graph is bipartite.
V0: 1 4 5 6 7 
V1: 2 3 8 9 10 11 12 13 14 15 
File: u4a-2.txt
The graph is bipartite.
V0: 1 4 5 6 7 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 
V1: 2 3 8 9 10 11 12 13 14 15 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 
File: u4a-3.txt
The graph is bipartite.
File: u4a-4.txt
The graph is bipartite.
File: u4a-5.txt
The graph is bipartite.
File: u4a-6.txt
The graph is bipartite.
File: u4a-7.txt
The graph is bipartite.
V0: 1 3 5 7 9 
V1: 2 4 6 8 10 
File: u4b-1.txt
The graph is not bipartite.
File: u4b-2.txt
The graph is not bipartite.
File: u4b-3.txt
The graph is not bipartite.
File: d4b-4.txt
The graph is not bipartite.
File: u4b-5.txt
The graph is not bipartite.
File: d4b-6.txt
The graph is not bipartite.
File: u4b-7.txt
The graph is not bipartite.
```