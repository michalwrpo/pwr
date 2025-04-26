import numpy as np
import networkx as nx
import random
import matplotlib.pyplot as plt

# --- Generowanie grafu ---
def generate_graph():
    G = nx.DiGraph()
    G.add_nodes_from(range(20))
    edges = [
        (0,1), (0,3), (1,4), (1,5), (2,3), (2,6),
        (3,7), (4,8), (5,9), (6,10), (7,11), (8,12),
        (9,13), (10,14), (11,15), (12,16), (13,17), (14,18),
        (15,19), (4,0), (6,1), (8,2), (10,5), (12,7), (14,9),
        (16,11), (17,18), (18,15), (19,16)
    ]
    G.add_edges_from(edges)
    return G

# --- Przypisanie przepustowości ---
def assign_capacities(G, m, flows, scale=1.0):
    caps = {}
    for e in G.edges():
        r = int(scale * random.randint(10000, 20000))
        while (r < m * flows[e]):
            r += 10000
        caps[e] = r
    return caps

# --- Losowa macierz N ---
def generate_N(size, scale=1):
    N = np.random.randint(1, 50, size=(size, size)) * scale
    np.fill_diagonal(N, 0)
    return N

# --- Przydziel przepływy losowo ---
def assign_flows(G, scale=1.0):
    return {e: int(random.randint(100, 300) * scale) for e in G.edges()} 

# --- Oblicz opóźnienie T ---
def compute_T(G, N, flows, capacities, m):
    total_packets = sum(sum(N))
    T = 0
    for e in G.edges():
        a, c = flows[e], capacities[e]
        if (c / m > a):
            T += a / (c / m - a)
        else 
    return T / total_packets if total_packets else 0

# --- Symulacja niezawodności ---
def simulate_reliability(G, N, flows, capacities, m, T_max, p, trials=500):
    success = 0
    for _ in range(trials):
        active_edges = [e for e in G.edges() if random.random() < p]
        subG = G.edge_subgraph(active_edges).copy()
        if nx.is_weakly_connected(subG):
            T = compute_T(subG, N, flows, capacities, m)
            if T < T_max:
                success += 1
    return success / trials

def experiment_1():
    G = generate_graph()
    N = generate_N(len(G.nodes()))
    T_max = 0.5
    p = 0.98
    m = 1000
    scales = np.linspace(1.0, 4.0, 10)
    results = []
    base_flows = assign_flows(G)
    capacities = assign_capacities(G, m, base_flows)

    for scale in scales:
        flows = assign_flows(G, scale)
        reliability = simulate_reliability(G, N, flows, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(scales, results, marker='o')
    plt.xlabel("Współczynnik skali macierzy N")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Natężenie strumienia")
    plt.grid(True)
    plt.show()

def experiment_2():
    G = generate_graph()
    N = generate_N(len(G.nodes()))
    flows = assign_flows(G, scale=1.5)
    m = 1000
    T_max = 0.5
    p = 0.98
    caps = np.arange(8000, 30000, 2000)
    results = []

    for scale in caps:
        capacities = assign_capacities(G, m, flows, scale)
        reliability = simulate_reliability(G, N, flows, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(caps, results, marker='s', color='green')
    plt.xlabel("Średnia przepustowość kanałów (bps)")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Przepustowość")
    plt.grid(True)
    plt.show()

def experiment_3():
    G = generate_graph()

    extra_edges = [(4,19), (6,11), (8,12), (10,15), (12,6), (14,19), (16,1), (17,3), (18,5), (19,6)]
    T_max = 0.5
    p = 0.98
    m = 1000
    scale = 1.3
    results = []
    flows = assign_flows(G, scale)
    capacities = assign_capacities(G, m, flows)
    mean_cap = int(np.mean(list(capacities.values())))

    for i in range(len(extra_edges) + 1):
        if i > 0:
            G.add_edge(extra_edges[i-1][0], extra_edges[i-1][1])

        N = generate_N(len(G.nodes()))
        flows[extra_edges[i-1]] = random.randint(100, 300)
        capacities[extra_edges[i-1]] = mean_cap
        reliability = simulate_reliability(G, N, flows, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(range(len(results)), results, color='orange')
    plt.xlabel("Liczba dodatkowych krawędzi")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Rozbudowa topologii")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    experiment_1()
    experiment_2()
    experiment_3()
