import random

# Konfiguracja
MEDIUM_LENGTH = 30
TICKS = 300
SIGNAL_SPEED = 1  # ile komórek pokonuje sygnał na tick
MAX_ATTEMPTS = 10

class Node:
    def __init__(self, name, position, send_time, distance):
        self.name = name
        self.position = position
        self.send_time = send_time
        self.distance = distance
        self.state = "idle"
        self.backoff = 0
        self.attempts = 0

    def __str__(self):
        return f"{self.name}@{self.position}"

def print_medium(medium):
    print("".join([c if c else "." for c in medium]))

def propagate_signal(medium, signals):
    new_signals = []
    for signal in signals:
        pos, direction, source = signal
        new_pos = pos + direction * SIGNAL_SPEED
        if 0 <= new_pos < len(medium):
            if medium[new_pos] is None:
                medium[new_pos] = source
            else:
                if medium[new_pos] != source:
                    medium[new_pos] = "X"  # kolizja
            new_signals.append((new_pos, direction, source))
    return new_signals

def is_medium_idle(medium, position):
    return medium[position] is None

def run_simulation(nodes):
    medium = [None] * MEDIUM_LENGTH
    signals = []
    time_log = []

    for tick in range(TICKS):
        print(f"\nTick {tick}")
        time_log.append("")
        
        # Propagacja sygnałów
        signals = propagate_signal(medium, signals)

        # Wysyłanie sygnału
        for node in nodes:
            if tick == node.send_time and node.state == "idle":
                if is_medium_idle(medium, node.position):
                    print(f"{node} zaczyna nadawać.")
                    medium[node.position] = node.name
                    signals.append((node.position, -1, node.name))  # lewa strona
                    signals.append((node.position, 1, node.name))   # prawa strona
                    node.state = "transmitting"
                else:
                    print(f"{node} wykrywa zajęte medium. Czeka.")
                    node.send_time += random.randint(1, 5)

            elif node.state == "transmitting":
                if tick >= node.send_time + 2 * node.distance:
                    print(f"{node} nie wykrywa kolizji")
                    node.state = "idle"
                    time_log[-1] += f"{node} SUKCES; "
                if medium[node.position] not in [node.name, None]:
                    print(f"{node} wykrywa kolizję!")
                    node.state = "backoff"
                    node.attempts += 1
                    if node.attempts < MAX_ATTEMPTS:
                        node.backoff = random.randint(1, 2 ** node.attempts)
                        node.send_time = tick + node.backoff
                    node.state = "idle"
                    time_log[-1] += f"{node} KOLIZJA; "

        # Wyświetl medium
        print_medium(medium)
        time_log[-1] = "".join([c if c else "." for c in medium]) + " " + time_log[-1]

        # Reset medium po każdym ticku (symuluje zanik sygnału po propagacji)
        medium = [None for _ in medium]

    print("\n=== Log symulacji ===")
    for i, line in enumerate(time_log):
        print(f"{i:02d}: {line}")


if __name__ == "__main__":
    nodes = [
        Node("A", 2, 1, 15),
        Node("B", 17, 1, 15),
        # Node("C", 10, 10),
    ]

    run_simulation(nodes)
