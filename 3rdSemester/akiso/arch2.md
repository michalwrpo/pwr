# Lecture 2

### Benchmark
- W języku wysokiego poziomu
- Reprezentatywny dla jakiegoś przypadku
- Mierzalny
- Powszechny (np. żeby nie tylko intel mógł odpalić)

### SPEC
Standard Performance Evaluation Comrporation <br>

Dla zestawu n testóœ:
- Skompiluj, uruchom trzykrotnie, weź medianę czasu wykonania
- Znormalizuj względem maszyny wzorcowej (wsk. referencyjny)
- Oblicz średnią geometryczną wszystkich wskaźników

### Inne testy

- Linpack (top-500)
- Livermore loops
- Dhrystone (int) / Whetstone (float)
- phoronix-test-suite / openbenchmark.org

### Niezawodność
Miara długości nieprzerwanego dostarczania usługi. <br>
MTTF - Mean Time To Failure <br>
1/MTTF = częstotliwość awarii; FIT (Failures in Time): w ujęciu miliarda godzin działania <br>

Zał.: żywotność komponentów mają ~ Exp (niezależne od czasu działania) <br>

- MIPS - Miliony instrukcji na sekundę

