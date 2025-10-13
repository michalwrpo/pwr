from sys import argv

def compute_prefix_function(pattern: str) -> list:
    m = len(pattern)
    pi = [0] * m
    k = 0

    for q in range(1, m):
        while k > 0 and pattern[k] != pattern[q]:
            k = pi[k - 1]
        if pattern[k] == pattern[q]:
            k += 1
        pi[q] = k

    return pi

def kmp_matcher(text: str, pattern: str) -> None:
    n = len(text)
    m = len(pattern)
    pi = compute_prefix_function(pattern)
    q = 0
    occurred = False

    for i in range(n):
        while q > 0 and pattern[q] != text[i]:
            q = pi[q - 1]
        if pattern[q] == text[i]:
            q += 1
        if q == m:
            print(f"Pattern occurs with shift {i - m + 1}")
            occurred = True
            q = pi[q - 1]

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

    kmp_matcher(text, pattern)