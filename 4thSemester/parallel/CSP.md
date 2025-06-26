# CSP - Communicating Sequential Processes

*Def.* Proces - niezależny składnik systemu komunikujący się ze swoim środowiskiem przez interfejsy. Z procesów może się składać większy system, który sam też jest procesem.

*Def.* Interfejs - zbiór zdarzeń

*Def.* Krok wykonania - etykietowane przejście $P_1 \xrightarrow{\mu} P_2$, gdzie $\mu$ to:
- Zdarzenie zewnętrzne
- Zdarzenie zakończenia $\checkmark$
- Zdarzenie wewnętrzne $\tau$

Zbiór zdarzeń zewnętrznych: $\Sigma$

Oznaczenia: $\Sigma^{\checkmark, \tau} = \Sigma \cup \{\checkmark, \tau\}$, $\Sigma^\checkmark = \Sigma \cup \{\checkmark\}$

*Def.* Reguły wnioskowania:

poprzednik 1  
poprzednik 2  
...   
poprzednik n  
\---------- [warunek]  
wniosek

*Def.* STOP - proces, który nie ma żadnych przejść

*Def.* Dla procesu $P$ i zdarzenia $a \in \Sigma$ wyrażenie $a \rightarrow P$ oznacza proces o następującej semantyce:

\--------------------  
$(a \rightarrow P) \xrightarrow{a} P$

czyli jest proces, który przechodzi w $P$ po zdarzeniu $a$.

*Def.* Dla $A \subseteq \Sigma$, jeśli $\forall a \in A$ zdefiniowany jest $P(a)$ to $x: A \rightarrow P(x)$ oznacza proces oferujący początkowy wybór zdarzeń $A$. Po wyborze i wystąpieniu zdarzenia $a$ proces ten dalej zachowuje się jak $P(a)$.

Czyli mamy kilka opcji postępowania dalej, w zależności od zdarzenia, które wystąpi.

Jeśli $A = \{a_1, a_2, ..., a_n\}$ alternatywna notacja

$a_1 \rightarrow P(a_1) \\ |a_2 \rightarrow P(a_2) \\ ... \\ |a_n \rightarrow P(a_n)$

### Zdarzenia złożone

Zdarzenie $c.v$ może oznaczać przesłanie wartości $v$ przez kanał $c$.

Niech $c$ będzie kanałem typu $T$, wtedy $\{c.t | t\in T\}$ to zdarzenia na kanale $c$. 

Oznaczenie: $c.T = \{c.t | t\in T\}$. Ogólniej $c.d.S.T = \{c.d.s.t | s \in S \land t \in T\}$



$c!v \rightarrow P$ rozumiemy jako wysłanie $v$ przez kanał $c$, po którym następuje $P$.

Jeśli dla każdego $x \in T$ zdefiniowane jest $P(x)$, to $c?x: T \rightarrow P(x)$ oznacza odbiór wartości $x$ z kanału, po którym następuje $P(x)$.

*Def.* SKIP to proces reprezentujący stan, w którym wykonanie jest zakończone. Może wykonać tylko $\checkmark$ i zatrzymać się.

### Rekursja

Nazwa procesu $N$ może być użyta jako składnik w definiującym go wyrażeniu.

Reguła rozwijania nazwy procesu $N$ związanego definicją $N = P$:

$P \xrightarrow{\mu} P' \\ 
----- [ N = P ] \\
N \xrightarrow{\mu} P'$

*Def.* Meta-operacja podstawienia: $P_1[P_2/N]$ - zastąpienie wolnych wystąpień $N$ w wyrażeniu $P_1$ wyrażeniem $P_2$.

### Wybór zewnętrzny

*Def.* $P_1 \square P_2$ oznacza wybór rozstrzygany przez pierwsze zdarzenie.

Reguły dotyczące przejść:

$P_1 \xrightarrow{a} P_1' \\
------ \\
P_1 \square P_2 \xrightarrow{a} P_1' \\
P_2 \square P_1 \xrightarrow{a} P_1'$

$P_1 \xrightarrow{\tau} P_1' \\
-------- \\
P_1 \square P_2 \xrightarrow{\tau} P_1'\square P_2 \\
P_2 \square P_1 \xrightarrow{\tau} P_2 \square P_1'$

### Indeksowany wybór zewnętrzny

*Def.* $I$ - skończony zbiór (może być pusty) indeksów.

$P_j \xrightarrow{a} P' \\
-------[j \in I] \\
\square_{i\in I} P_i \xrightarrow{a} P'$

$P_j \xrightarrow{\tau} P_j' \\
---------[j \in I] \\
\square_{i\in I} P_i \xrightarrow{\tau} \square_{i\in I} P_i'$

### Wybór wewnętrzny

*Def.* $P_1 \sqcap P_2$ oznacza niedeterministyczny wybór między procesem $P_1$ a $P_2$.

Reguła przejść

$-------- \\
(P_1 \sqcap P_2) \xrightarrow{\tau} P_1 \\
(P_1 \sqcap P_2) \xrightarrow{\tau} P_2$

$\sqcap_{i \in J} P_i$ oznacza proces, który może się zachować jak dowolny $P_i$, dla $i \in J$.

### Alphabetized Parallel

*Def.* Dla procesu $P_1$ z interfejsem $A \subseteq \Sigma$ i $P_2$ z interfejsem $B \subseteq \Sigma$ wyrażenie $P_{1\texttt{ } A}\parallel_B P_2$ oznacza proces, w którym $P_1$ może wykonać zdarzenie z $A \backslash B$ albo $P_2$ może wykonać zdarzenie z $B \backslash A$ albo $P_1$ i $P_2$ jednocześnie wykonają zdarzenie z $A \cap B$. 

Jeśli $I$ jest skończonym zbiorem takim, że $P_i$ z alfabetem $A_i$ jest zdefiniowany dla każdego $i \in I$, to $\parallel^{i \in I}_{A_i} P_i$ oznacza równoległe złożenie wszystkich $P_i$.

### Przeplot

$P_1 ||| P_2$ proces w którym zdarzenia $P_1$ i $P_2$ dowolnie się przeplatają. (Synchornizują się jedynie na $\checkmark$.)

### Interface Parallel

*Def.* Dla $A \subseteq \Sigma$: $P_{1\texttt{ }A}^{\texttt{\char32\char32}\parallel} P_2$

$P_1 \xrightarrow{a} P_1' \\$
$P_2 \xrightarrow{a} P_2' \\$
$----------[a \in A^\checkmark] \\$
$P_{1\texttt{ }A}^{\texttt{\char32\char32}\parallel} P_2 \xrightarrow{a} P_{1\texttt{ }A}^{\texttt{'\char32}\parallel} P_2'$

$P_1 \xrightarrow{\mu} P_1' \\$
$----------[\mu \notin A^\checkmark] \\$
$P_{1\texttt{ }A}^{\texttt{\char32\char32}\parallel} P_2 \xrightarrow{a} P_{1\texttt{ }A}^{\texttt{'\char32}\parallel} P_2 \\$
$P_{2\texttt{ }A}^{\texttt{\char32\char32}\parallel} P_1 \xrightarrow{a} P_{2\texttt{ }A}^{\texttt{\char32}\parallel} P_1'$

### Hiding

*Def.* $P \backslash A$ oznacza proces z którego interfejsu usunięto zdarzenia z $A$.

$P_1 \xrightarrow{a} P_1' \\$
$-------[a \in A] \\$
$P\backslash A \xrightarrow{\tau} P' \backslash A$

$P_1 \xrightarrow{\mu} P_1' \\$
$-------[\mu \notin A] \\$
$P\backslash A \xrightarrow{\mu} P' \backslash A$

### Forward renaming

Zakładamy, że $f: \Sigma^\checkmark \rightarrow \Sigma^\checkmark \\$
$f(a) = \checkmark \iff a = \checkmark\\$
$f(P)$ wykonuje zdarzenie $f(a)$ wtedy gdy $P$ wykonałoby $a$.

$P \xrightarrow{a} P' \\$
$-------- \\$
$f(P) \xrightarrow{f(a)} f(P')$

$P \xrightarrow{\tau} P' \\$
$-------- \\$
$f(P) \xrightarrow{\tau} f(P')$

### Etykietowanie

$f_l(x) = l.x$ dla $x \in \Sigma$ i $f_l(\checkmark) = \checkmark$. Zamiast $f_l(P)$ piszemy $l : P$.

### Backwards renaming

*Def.* $f^{-1}(P)$ może wykonać $a$, gdy $P$ może wykonać $f(a)$.

$P \xrightarrow{f(a)} P' \\$
$-------- \\$
$f^{-1}(P) \xrightarrow{a} f^{-1}(P')$

$P \xrightarrow{\tau} P' \\$
$-------- \\$
$f^{-1}(P) \xrightarrow{\tau} f^{-1}(P')$

### Chaining

Niech $P_1$, $P_2$ - procesy o dwóch kanałach $in$ i $out$

$swap_{c,d}(c.x) = d.x\\$
$swap_{c,d}(d.x) = c.x\\$
$swap_{c,d}(y) = y$ jeśli $y \neq c.x \land y \neq d.x$

Wtedy:

$P_1 \gg P_2 \iff (swap_{out,mid}(P_1) \parallel swap_{in, mid}(P_2)) \backslash \{mid\}$

czyli $P_2$ czyta z outputu $P_1$ i nie możemy bezpośrednio oddziaływać na kanał $mid$, który je łączy (pipowanie).

### Sekwencja procesóœ

*Def.* $P_1;P_2$ - sekwencja $P_1$ i $P_2$

$P_1 \xrightarrow{\mu} P_1'\\$
$--------[\mu \neq \checkmark]\\$
$P_1;P_2 \xrightarrow{\mu} P_1';P_2$

$P_1 \xrightarrow{\checkmark} P_1'\\$
$------\\$
$P_1;P_2 \xrightarrow{\tau} P_2$

### Przerwania

*Def.* $P_1 \bigtriangleup P_2$ oznacza $P_1$ może być przerwany przez $P_2$.

$P_1 \xrightarrow{\mu} P_1'\\$
$--------[\mu \neq \checkmark]\\$
$P_1 \bigtriangleup P_2 \xrightarrow{\mu} P_1' \bigtriangleup P_2$

$P_1 \xrightarrow{\checkmark} P_1'\\$
$------\\$
$P_1 \bigtriangleup P_2 \xrightarrow{\checkmark} P_1'$

$P_2 \xrightarrow{\tau} P_2'\\$
$--------\\$
$P_1 \bigtriangleup P_2 \xrightarrow{\tau} P_1 \bigtriangleup P_2'$

$P_2 \xrightarrow{a} P_2'\\$
$------\\$
$P_1 \bigtriangleup P_2 \xrightarrow{a} P_2'$

## Traces

*Def.* $traces(P)$ zbiór możliwych prefiksów ciągów widocznych zdarzeń pozostawionych przez proces $P$.

### Notacja dot. ciągów

- $\langle \rangle$ - ciąg pusty
- $A*$ - ciągi elementów zbioru $A$
- Dla niepustego ciągu $seq = \langle a \rangle \frown seq'$, $head(seq) = a$ i $tail(seq) = seq'$ 
- Dla niepustego ciągu $seq = seq'' \frown \langle b \rangle$, $foot(seq) = b$ i $init(seq) = seq''$ 
- $\#seq$ - długość $seq$
- $a$ in $seq$ - $a$ występuje w $seq$
- $\sigma(seq)$ - zbiór elementów występujących w $seq$
- Prefix: $seq \leqslant seq_1 \iff \exists_{seq_2} seq \frown seq_2 = seq_1$
- $seq \leqslant_n seq_1 \iff \exists_{seq_2} seq \frown seq_2 = seq_1 \land \#seq_2 \leq n$
- $seq \preccurlyeq seq_1$ - $seq$ jest podciągiem $seq_1$ (niekoniecznie ciągłym)
- Projekcja na $A$: $seq \upharpoonright A$ - podciąg $seq$ elementów z $A$
- $seq \backslash A$ - podciąg $seq$ bez elementów z $A$
- $seq \downarrow A = \#(seq \upharpoonright A)$
- $seq \downarrow \{a\} = seq \downarrow a$

### Notacja dot. śladów

$TRACE = \{ tr | \sigma(tr) \subseteq \Sigma^{\checkmark} \land \#tr \in \mathbb{N} \land \checkmark \notin \sigma(init(tr))\}$

$channel(c.v) = c\\$
$value(c.v) = v\\$
$CHANNELS(tr) = \{channel(x) | x \textbf{ in } tr\}\\$
$tr \Downarrow c = \langle value(x) | x \leftarrow tr, channel(x) = c \rangle\\$
$tr \Downarrow C = \langle value(x) | x \leftarrow tr, channel(x) \in C \rangle$

$P \xRightarrow{tr} P'$ oznacza, że istnieje ciąg przejść od początkowego procesu $P$ do $P'$ i widoczne z tych przejść tworzą ślad $tr$.

$P \xRightarrow{tr} \iff (\exists P') P \xRightarrow{tr} P'\\$
$traces(P) = \{tr | P \xRightarrow{tr}\}$

### Trace Semantics

$P_1 =_T P_2 \iff traces(P_1) = traces(P_2)$

Dla każdego procesu $P$, jeśli $S = traces(P)$ to
1. $\langle \rangle \in S$
2. $(\forall tr_1, tr_2 \in TRACE) (tr_1 \leqslant tr_2 \land tr_2 \in S \Rightarrow tr_1 \in S)$


$traces(STOP) = \{\langle \rangle\}$

$traces(a \rightarrow P) = \{\langle \rangle\} \cup \{ \langle a \rangle \frown tr | tr \in traces(P)\}$

$traces(x: A \rightarrow P(x)) = \{\langle \rangle\} \cup \{ \langle a \rangle \frown tr | a \in A \land tr \in traces(P(a))\}$

$traces(c!v \rightarrow P) = \{\langle \rangle\} \cup \{ \langle c.v \rangle \frown tr |\land tr \in traces(P)\}$

$traces(c?m: T \rightarrow P(m)) = \{\langle \rangle\} \cup \{ \langle c.v \rangle \frown tr | v \in T \land tr \in traces(P(v))\}$

$traces(SKIP) = \{ \langle \rangle, \langle \checkmark \rangle\}$

### RUN

$traces(RUN) = \{ tr | tr \in TRACE\}$

$RUN = (x : \Sigma \rightarrow RUN) \square SKIP$

$traces(RUN_A) = \{ tr | tr \in TRACE \land \sigma(tr) \subseteq A\}$

$RUN_A = x : A \rightarrow RUN$

$RUN_{A^\checkmark} = x : A \rightarrow RUN \square SKIP$

### External Choice

$traces(P_1 \square P_2) = traces(P_1) \cup traces(P_2)$

**Prawa:**
1. $P\square P = P$
2. $P_1 \square (P_2 \square P_3) = (P_1 \square P_2) \square P_3$
3. $P_1 \square P_2 = P_2 \square P_1$
4. $P\square STOP = P$
5. $P \square RUN =_T RUN$
6. $x: A \rightarrow P_1(x) \square y : B \rightarrow P_2(y) = \\ z : A \cup B \rightarrow R(z)$, gdzie: 
$\\ R(c) = P_1(c)$ if $c \in A \backslash B \\$
$R(c) = P_2(c)$ if $c \in B \backslash A \\$
$R(c) = P_1(c) \sqcap P_2(c)$ if $c \in A \cap B \\$

### Internal Choice

$traces(P_1 \sqcap P_2) = traces(P_1) \cup traces(P_2)$

**Prawa:**
1. $P\sqcap P = P$
2. $P_1 \sqcap (P_2 \sqcap P_3) = (P_1 \sqcap P_2) \sqcap P_3$
3. $P_1 \sqcap P_2 = P_2 \sqcap P_1$
4. $P_1 \sqcap P_2 =_T P_1 \square P_2$

### Alphabetized Parallel

$traces(P_{1 A} \parallel_B P_2) = \{ tr \in TRACE | tr \upharpoonright A^\checkmark \in traces(P_1) \land tr \upharpoonright B^\checkmark \in traces(P_2) \land \sigma(tr) \subseteq (A \cup B)^\checkmark \}$

### Interleaving

- $\langle \rangle$ interleaves $tr_1$, $tr_2 \iff tr_1 = tr_2 = \langle \rangle$
- $\langle \checkmark \rangle$ interleaves $tr_1$, $tr_2 \iff tr_1 = tr_2 = \langle \checkmark \rangle$
- $\langle a \rangle \frown tr \neq \langle \checkmark \rangle \Rightarrow \\$
$\langle a \rangle \frown tr$ interleaves $tr_1$, $tr_2 \iff \\ (head(tr_1) = a \land tr$ interleaves $tail(tr_1)$, $tr_2) \lor \\$
$(head(tr_2) = a \land tr$ interleaves $tr_1$, $tail(tr_2))$ 

$traces(P_1 ||| P_2) = \{ tr \in TRACE | (\exists tr_1, tr_2) tr_1 \in traces(P_1) \land tr_2 \in traces(P_2) \land tr$ interleaves $tr_1, tr_2\}$

### Interface parallel

Dla $A \in \Sigma$
- $\langle \rangle synch_A$ $tr_1, tr_2 \iff tr_1 = tr_2 = \langle \rangle$
- $\langle \checkmark \rangle synch_A$ $tr_1, tr_2 \iff tr_1 = tr_2 = \langle \checkmark \rangle$
- $\langle a \rangle \frown tr \neq \langle \checkmark \rangle \Rightarrow \\$
$\langle a \rangle \frown tr$ $synch_A$ $tr_1, tr_2 \iff \\$
$(a \in A \land head(tr_1) = head(tr_2) = a \land tr$ $sync_A$ $tail(tr_1), tail(tr_2)) \lor \\$
$(a \notin A \land (head(tr_1) = a \land tr$ $synch_A$ $tail(tr_1), tr_2 \lor\\$
$head(tr_2) = a \land tr$ $synch_A$ $tr_1, tail(tr_2)))$

**Prawa:**
- $P_{1 A}\parallel_B P_2 = P_1 \begin{array}{c} \parallel \\ A \cap B \end{array} P_2$ if $\alpha(P_1) \subseteq A \land \alpha(P_2) \subseteq B$
- $P_1 ||| P_2 = P_1 \begin{array}{c} \parallel \\ \{\} \end{array} P_2$

### Hiding

$traces(P \backslash A) = \{ tr \backslash A | tr \in traces(P)\}$

### Renaming

$traces(f(P)) = \{ f(tr)| tr \in traces(P)\}$

### Rekursja

Dla $N = F(N)$ mamy $traces(N) = \bigcup_{n \in \mathbb{N}} traces(F^n(STOP))$

### Guardedness

Nazwa $N$ jest chroniona (guarded) w $F(N)$, jeśli w każdym wykonaniu $F(N)$ wykonanie $N$ jest poprzedzone wykonaniem widocznego zdarzenia.

Nazwa procesu $N$ jest chroniona (event guarded) w wyrażeniu $P$, jeśli:
- $N$ nie występuje w $P$ albo
- $P$ nie zawiera operatora "\" oraz każde wystąpienie $N$ jest
  - W zakresie operatora prefix, prefix choice, input lub output; albo
  - zawarte w drugim argumencie ";", gdzie pierwszy argument nie kończy się natychmiast.

($P$ kończy się natychmiast jeśli jednym z jego śladów jest $\langle \checkmark \rangle$)

### UFP (Unique Fixed Point)

$(F(Y)$ guarded $\land (F(P_1) =_T P_1) \land (F(P_2) =_T P_2)) \Rightarrow P_1 =_T P_2$

### Specyfikacja

Niech $S(tr)$ predykat określony dla śladów $tr$. Proces $P$ spełnia specyfikację $S(tr)$, jeśli $S(tr)$ jest spełnione dla każdego śladu $tr$ procesu $P$.

$P \textbf{ sat } S(tr) \iff (\forall tr \in traces(P)) S(tr)$

### Weryfikacja

System dowodzenia: zbiór reguł dla wszystkich operatorów pozwalających wnioskować specyfikacje dla złożonych procesów z założeń dotyczących specyfikacji składowych.

$S(tr)$ jest $A$-independent, jeśli $(\forall tr) S(tr) \iff S(tr\backslash A)$

### Process-oriented specification

$P_1$ spełnia specyfikację $P_0$, jeśli każdy ślad $P_1$ jest jakimś śladem $P_0$.

$P_0 \sqsubseteq_T P_1 = traces(P_1) \subseteq traces(P_0)$

Alternatywnie:

$P_0 \sqsubseteq_T P_1 = (P_0 =_T P_0 \sqcap P_1)$

Jeśli funkcja $F(Y)$ jest skonstruowana przy pomocy operatorów CSP, to $P_0 \sqsubseteq P_1 \Rightarrow F(P_0) \sqsubseteq F(P_1)$, czyli operatory CSP są monotoniczne ze względu na refinement.

### Stable Refusals

Proces jest stabilny (ozn. $P \downarrow$) jeśli nie może wykonać wewnętrznego przejścia.

Jeśli środowisko oferuje zbiór zdarzeń $X \subseteq \Sigma^\checkmark$ i stabilny $P$ może wykonać któreś z nich, to zdarzenie nastąpi. W przeciwnym razie $P$ odrzuca cały zbiór $X$.

$X$ jest refusal dla $P$ ($P$ **ref** $X$), jeśli $P$ może się zablokować mając do dyspozycji jedynie zdarzenia $X$.

### Divergence

Proces $P$ jest divergent (ozn. $P \uparrow$), jeśli może w nieskończoność wykonywać jedynie zdarzenia wewnętrzne.

Proces jest divergece-free, jeśli żaden z jego stanów nie jest divergent.

Jeśli $P$ jest non-divergent to na pewno wykona jakieś zdarzenie z oferowanego zbioru $A$ wtedy i tylko wtedy, gdy $A$ nie jest refusal dla $P$.

### Stable failures

$(tr, X)$ jest stable failure dla $P$, jeśli: $(\exists P'') P \xRightarrow{tr} P'' \land P'' \downarrow \land P'' \textbf{ ref } X$

Dwa procesy uznajemy za równoważne, jeśli mają taki sam zbiór śladów (traces) i stable failures.

$\mathcal{SF}[P]$ - zbiór stable failures $P$

### DIV

Proces, który nic nie robi tylko "odpływa" (diverges)

$traces(DIV) = \{\langle \rangle\} \\$
$\mathcal{SF}[DIV] = \{\}$

### CHAOS

Proces, który może robić cokolwiek, poza "odpływaniem". (Może akceptować lub odrzucać dowolne zdarzenie i zawsze się stabilizuje.)

$traces(CHAOS) = TRACE \\$
$\mathcal{SF}[CHAOS] = TRACE \times \mathbb{P}(\Sigma^\checkmark)$

### Rekursja

W definicji rekurencyjnej $N = P$, proces $P$ ze zmienną wolną $N$ odpowiada funkcji $F(Y) = P[Y/N]$.

Zbiór SF:

$\bigcup_{n \in \mathbb{N}} \mathcal{SF}[F^n(DIV)]$

### UFP

$(F(Y)$ guarded $\land (F(P_1) =_{SF} P_1) \land (F(P_2) =_{SF} P_2)) \Rightarrow P_1 =_{SF} P_2$