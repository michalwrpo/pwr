# Lecture 1

Literatura:
- K. Sayood, Kompresja danych - wprowadzenie, READ ME 2002 (ISBN 83-7243-094-2)
- A. Przelaskowski, Kompresja danych, BTC 2005 (ISBN: 83-60233-05-5)
- J. Adamek, Fundations of Coding, Wiley 1991 (ISBN 0-47-162187-0)


## Kompresja
- Kompresja bezstratna: z postaci skompresowanej zawsze można odtworzyć postać identyczną z oryginałem.
- Kompresja stratna: dopuszcza pewien poziom utraty informacji w zamian za lepszy współczennik kompresji.

# Rodzaje kodów
- Kody stałej długości - np. kody ASCII
- Kody o różnej długości - np. kody prefiksowe, kod Morse'a

## Kompresja cd.
Nie istnieje algorytm kompresji bezstratnej, który kompresuje wszystkie podane mu dane.
- Różnych danych długości n jest $2^n$.
- Ciągów długości mniejszej niż n jest $2^n - 1$. 

