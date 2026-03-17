from typing import List, Tuple, Dict, Set
import numpy as np
import sys

class Graph:
    class Node:
        def __init__(self, id: int, x: float, y: float) -> None:
            self.id = id
            self.visited = False
            self.x = x
            self.y = y

    class Edge:
        def __init__(self, v1: int, v2: int, length: int) -> None:
            self.v1 = v1
            self.v2 = v2
            self.length = length            


    def __init__(self, points: List[Tuple[int, float, float]]):
        self.nodes : Dict[int, Graph.Node] = {}
        self.edges : List[Graph.Edge] = []
        self.mst : List[Graph.Edge] = []
        self.groups : List[Set[int]] = [{p[0]} for p in points]

        for p1 in points:
            self.nodes[p1[0]] = self.Node(p1[0], p1[1], p1[2])
            for p2 in points:
                if p1[0] >= p2[0]:
                    continue
                distance = np.sqrt((p1[1] - p2[1])**2 + (p1[2] - p2[2])**2)
                self.edges.append(self.Edge(p1[0], p2[0], round(distance)))

        self.kruskal()

    def sort_edges(self):
        self.edges.sort(key=lambda e: e.length)

    def kruskal(self):
        self.sort_edges()

        for e in self.edges:
            if len(self.groups) == 1:
                break

            n1 = self.nodes[e.v1]
            n2 = self.nodes[e.v2]
            id1, id2 = 0, 0
            for i in range(len(self.groups)):
                if n1.id in self.groups[i]:
                    id1 = i
                if n2.id in self.groups[i]:
                    id2 = i

            if id1 != id2:
                self.mst.append(e)
                self.groups[id1].update(self.groups[id2])
                self.groups.pop(id2)

    def mst_len(self) -> int:
        length = 0
        for e in self.mst:
            n1 = self.nodes[e.v1]
            n2 = self.nodes[e.v2]

            length += round(np.sqrt((n1.x - n2.x)**2 + (n1.y - n2.y)**2))

        return length

    def DFS(self, v: int):
        s = []
        s.append(v)
        self.order : List[int] = []

        while len(s) > 0:
            v = s.pop()
            if not self.nodes[v].visited:
                self.order.append(v)
                self.nodes[v].visited = True
                for e in self.mst:
                    if e.v1 == v:
                        s.append(e.v2)
                    elif e.v2 == v:
                        s.append(e.v1)

    def cycle_len(self) -> int:
        total_dist = 0
        for i in range(len(self.order)):
            next_i = (i + 1) % len(self.order)
            n1 = self.nodes[self.order[i]]
            n2 = self.nodes[self.order[next_i]]
            dist = round(np.sqrt((n1.x - n2.x)**2 + (n1.y - n2.y)**2))
            total_dist += dist

        return total_dist



def load_data(filename: str) -> List[Tuple[int, float, float]]:
    parsed = []

    with open(filename, 'r') as file:
        data = file.read().split("\n")
        for line in data:
            if line == "" or line[0].isalpha():
                continue

            split = line.split(" ")
            entry = (int(split[0]), float(split[1]), float(split[2]))

            parsed.append(entry)

    return parsed


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Input filename not given.")
        sys.exit(1)

    data = load_data(sys.argv[1])

    graph = Graph(data)

    print(f"MST weight: {graph.mst_len()}")

    graph.DFS(1)

    print(f"Path length: {graph.cycle_len()}")

    