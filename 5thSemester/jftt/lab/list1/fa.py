from sys import argv

def compute_transition_function(pattern:str, alphabet:set) -> dict:
    m = len(pattern)
    transition_function = {}
    
    for q in range(m + 1):
        for a in alphabet:
            k = min(m, q + 1)
            while pattern[:k] != (pattern[:q] + a)[-k:]:
                k -= 1
            transition_function[(q, a)] = k
            
    return transition_function

def finite_automaton_matcher(text:str, pattern:str) -> None:
    alphabet = set(pattern)
    transition_function = compute_transition_function(pattern, alphabet)
    m = len(pattern)
    n = len(text)
    q = 0
    occurred = False

    for i in range(n):
        a = text[i]
        if a in alphabet:
            q = transition_function.get((q, a), 0)
        else:
            q = 0
        if q == m:
            print(f"Pattern occurs with shift {i - m + 1}")
            occurred = True

    if not occurred:
        print("Pattern does not occur in the text")

if __name__ == "__main__":
    if len(argv) != 3:
        print(f"Usage: python {argv[0]} <pattern> <file name>")
        exit(-1)
    else:
        pattern = argv[1]
        filename = argv[2]

    with open(filename, 'r') as file:
        text = file.read()

    finite_automaton_matcher(text, pattern)
        