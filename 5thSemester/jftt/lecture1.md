# Lecture 1


Literatura:
- A.V. Aho, R. Sethi, J.D. Ullman, Kompilatory. Reguły, metody i narzędzia, WNT, Warszawa 2002, (ISBN: 83-204-2656-1)
- .E. Hopcroft, J.D. Ullman, Wprowadzenie do teorii automatów, języków i obliczeń, WNT, Warszawa 1994 (ISBN 83-01-11298-0)
- T.A. Sudkamp, Languages and Machines, Pearson, 2006, (ISBN: 978-81-317-1475-1)

## Podstawowe definicje

- Alfabet ($\Sigma$) - skończony zbiór symboli.
- Słowo - skończony ciąg symboli z alfabetu.
- Język - zbiór słów nad danym alfabetem ($\emptyset$ - język pusty).
- $\epsilon$ - słowo puste.

## Deterministyczny Automat Skończony (DFA)

Deterministyczny automat skończony to uporządkowana piątka (Q, $\Sigma$, $\delta$, $q_0$, F), gdzie
- Q - skończony zbiór stanów
- $\Sigma$ - skończony alfabet wejściowy
- $\delta$ - funkcja przejścia postaci $Q \times \Sigma \rightarrow Q$
- $q_0$ - stan początkowy
- $F \subseteq Q$ - zbiór stanów akceptujących

$\delta$ możemy rozszerzyć do $\hat\delta: Q \times \Sigma^* \rightarrow Q$ zgodną z definicją rekurencją $\hat\delta(q, \epsilon) = q$ i $\hat\delta(q, wa) = \delta(\delta(q, w), a)$.

## Niedeterministyczny Automat Skończony (NFA)

Istnieje zero, jedno lub więcej przejść ze stanu przy tym samym symbolu wejściowym. 
$\delta: Q \times \Sigma \rightarrow 2^Q$

Automat niedeterministyczny akceptuje słowo w jeżeli istnieje odpowiadający mu ciąg przejść ze stanu początkowego do stanu akceptującego.

Dopuszczamy przejścia między stanami bez symboli wejściowych. $\delta: Q \times (\Sigma \cup \{\epsilon\}) \rightarrow 2^Q$
<br>*(teleportacja)*
