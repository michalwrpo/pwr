import random

# Konfiguracja
MEDIUM_LENGTH = 80
TICKS = 20000
SIGNAL_SPEED = 1  # ile komórek pokonuje sygnał na tick
MAX_ATTEMPTS = 16
INCREASES = 10

class Node:
    def __init__(self, name, position, send_time):
        self.name = name
        self.position = position
        self.send_time = send_time
        self.state = "idle"
        self.backoff = 0
        self.attempts = 0
        self.jam_start = 0

    def __str__(self):
        return f"{self.name}@{self.position}"

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
    success = 0

    for tick in range(TICKS):
        time_log.append("")
        
        # Propagacja sygnałów
        signals = propagate_signal(medium, signals)

        # Wysyłanie sygnału
        for node in nodes:
            if tick == node.send_time and node.state == "idle":
                if is_medium_idle(medium, node.position):
                    medium[node.position] = node.name
                    signals.append((node.position, -1, node.name))  # lewa strona
                    signals.append((node.position, 1, node.name))   # prawa strona
                    node.state = "transmitting"
                else:
                    node.send_time += 1

            elif node.state == "transmitting":
                if medium[node.position] not in [node.name, None]:
                    node.state = "backoff"
                    if node.attempts < MAX_ATTEMPTS:
                        if node.attempts < INCREASES:
                            node.backoff = 2 * MEDIUM_LENGTH * random.randint(0, 2 ** (node.attempts + 1) - 1)
                        node.send_time = tick + 2 * MEDIUM_LENGTH + 1 + node.backoff
                    node.attempts += 1
                    node.state = "jam"
                    node.jam_start = tick
                    medium[node.position] = "X"
                    time_log[-1] += f"{node} KOLIZJA; "
                else: 
                    if tick >= node.send_time + 2 * MEDIUM_LENGTH:
                        node.state = "idle"
                        success += 1
                        time_log[-1] += f"{node} SUKCES; "
                    else:
                        medium[node.position] = node.name
                        signals.append((node.position, -1, node.name))  # lewa strona
                        signals.append((node.position, 1, node.name))   # prawa strona
            elif node.state == "jam":
                if tick >= node.jam_start + 2 * MEDIUM_LENGTH:
                    node.state = "idle"
                else:
                    medium[node.position] = "X"
                    signals.append((node.position, -1, "X"))  # lewa strona
                    signals.append((node.position, 1, "X"))   # prawa strona


        # Wyświetl medium
        time_log[-1] = "".join([c if c else "." for c in medium]) + " " + time_log[-1]

        # Reset medium po każdym ticku (symuluje zanik sygnału po propagacji)
        medium = [None for _ in medium]

        if success == len(nodes):
            break

    print("=== Log symulacji ===")
    for i in range(len(time_log) - 1, 0, -1):
        if time_log[i] == "".join(["." for _ in range(MEDIUM_LENGTH)]) + " ":
            time_log.pop(i)
        else:
            break
    for line in time_log:
        print(line)


if __name__ == "__main__":
    nodes = [
        Node("A", 2, 1),
        Node("B", 17, 1),
        Node("C", 10, 10),
    ]

    run_simulation(nodes)
