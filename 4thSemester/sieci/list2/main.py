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
        (16,11), (17,13), (18,15), (19,16)
    ]
    G.add_edges_from(edges)
    return G

# --- Przypisanie przepustowości ---
def assign_capacities(G, scale=1.0):
    return {e: int(scale * random.randint(10000, 20000)) for e in G.edges()}

# --- Losowa macierz N ---
def generate_N(size, scale=1.0):
    N = np.random.randint(1, 5, size=(size, size)) * scale
    np.fill_diagonal(N, 0)
    return N

# --- Przydziel przepływy losowo ---
def assign_flows(G, N):
    flows = {e: random.randint(100, 300) for e in G.edges()}
    return flows

# --- Oblicz opóźnienie T ---
def compute_T(G, flows, capacities, m):
    total_packets = sum(flows.values())
    T = 0
    for e in G.edges():
        a, c = flows[e], capacities[e]
        if c > a:
            T += a / (c / m - a)
    return T / total_packets if total_packets else 0

# --- Symulacja niezawodności ---
def simulate_reliability(G, flows, capacities, m, T_max, p, trials=500):
    success = 0
    for _ in range(trials):
        active_edges = [e for e in G.edges() if random.random() < p]
        subG = G.edge_subgraph(active_edges).copy()
        if nx.is_weakly_connected(subG):
            T = compute_T(subG, flows, capacities, m)
            if T < T_max:
                success += 1
    return success / trials

def experiment_1():
    G = generate_graph()
    capacities = assign_capacities(G)
    m = 1000
    T_max = 1.0
    p = 0.98
    scales = np.linspace(0.5, 3.0, 10)
    results = []

    for scale in scales:
        flows = assign_flows(G, scale=scale)
        reliability = simulate_reliability(G, flows, capacities, m, T_max, p)
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
    base_flows = assign_flows(G, scale=1.5)
    m = 1000
    T_max = 1.0
    p = 0.98
    caps = np.arange(8000, 30000, 2000)
    results = []

    for base in caps:
        capacities = assign_capacities(G, base=base)
        reliability = simulate_reliability(G, base_flows, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(caps, results, marker='s', color='green')
    plt.xlabel("Średnia przepustowość kanałów (bps)")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Przepustowość")
    plt.grid(True)
    plt.show()

def experiment_3():
    base_edges = [
        (0,1), (0,3), (1,4), (1,5), (2,3), (2,6),
        (3,7), (4,8), (5,9), (6,10), (7,11), (8,12),
        (9,13), (10,14), (11,15), (12,16), (13,17), (14,18),
        (15,19)
    ]
    G = nx.DiGraph()
    G.add_nodes_from(range(20))
    G.add_edges_from(base_edges)

    extra_edges = [(4,0), (6,1), (8,2), (10,5), (12,7), (14,9), (16,11), (17,13), (18,15), (19,16)]
    m = 1000
    T_max = 1.0
    p = 0.98
    results = []
    step_graphs = []

    base_flows = assign_flows(G, scale=1.3)
    base_capacities = assign_capacities(G)
    mean_cap = int(np.mean(list(base_capacities.values())))

    for i in range(len(extra_edges) + 1):
        Gi = nx.DiGraph()
        Gi.add_nodes_from(G.nodes())
        Gi.add_edges_from(base_edges + extra_edges[:i])
        flows = assign_flows(Gi, scale=1.3)
        capacities = {e: mean_cap for e in Gi.edges()}
        reliability = simulate_reliability(Gi, flows, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(range(len(results)), results, marker='^', color='orange')
    plt.xlabel("Liczba dodatkowych krawędzi")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Rozbudowa topologii")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    experiment_1()
    experiment_2()
    experiment_3()
