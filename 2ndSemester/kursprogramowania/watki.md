Linia czasu

Dysk -- nic, czekamy az sie zapisze -- | scanf i czekamy


RAM
MHz
Clock Latency - liczba cyckli, ktore musimy poczekac

RAM - wolny, procesor - szybki

Alogrytmy

Rownolegle - 

Wspolbiezne - > MAP reduce
Rozproszone - >

HPC - High Performance Computing

Watki sie przeplataja - mikrosekundy

Przeplot

zle:

```
int n = 3; 
f()
{ 
    if ( ++n >= 5)
        n = 0;

// Never Claim -> Promela | Spark
    assert(n < 5);

}
```

lepiej:

```
f()
{
    ++n;
    if(n >= 5)
        n = 0;

    assert(n < 5);
}
```

| T_1                | T_2 |
| ---                | --- |
| ++n (n = 4)        | \-\-\-\-\-  |
| if(n >= 5) (false) | \-\-\-\-\-  |
| \-\-\-\-\-         | ++n (n = 5) |
| assert(n < 5) boom | \-\-\-\-\-  |

```
f()
{
    LOCK
    if (++n >= 5)  //
        n = 0;     // Sekcja
                   // Krytyczna
    assert(n < 5)  //
    UNLOCK
}

```

| T_1 | T_2 |
| ---- | ---- | 
| LOCK | \-\-\-\-\- |
| ++n | LOCK -> WAIT / IDLE |
| if( n >= 5) | \-\-\-\-\- |
| n = 0       | \-\-\-\-\- |
| assert | \-\-\-\-\- |
| UNLOCK | \-\-\-\-\- |
| \-\-\-\-\- | LOCK |


Java

```
Object o = new Object();
synchronized(o)
{
    sekcja krytyczna
}
```

```
synchronized f()
{

}
```
=
```
f()
{
    sync(this)
    {

    }
}
```

^ To nie zadziala do listy (... Pacyna)

```
C c1 = new C();
C c2 = new C();
```


```
class C
    synchronized bool isActive();
    synchronized void activate();
    synchronized void desactivate();
```

Problem 5 filozofow
DEADLOCK

Zalozenia
na 4: 
    1. Gdy watek T_x zacznie zmieniac kolor, nikt nie moze czytac jego koloru, dopoki nie skonczy zmiany.
na 5: 
    2. Gdy zmieniam kolor nie zasypiam
    3. Gdy ktos czyta moj kolor nie zasypiam
    4. Gdy ktos czyta moj stan nie zmieniam stanu
    5. Jesli moj sasiad zmienia kolor, nie zmieniam stanu


    2 boxy: T1   T2

```
class T
    sync changeColor()
    sync getColor()
```

Mozliwosci:
T1.changeColor()
T2.refT2.getColor()


```
class Pane
    final Object locker = new Object();

    for (...)
        for (...)
            arr[i][j] = new T(locker); 
```

Tworzenie watkow z referencja do lockera

```
void changeColor()
{
    sync(locker)
    {
        ...
    }
}
```

```
class T
    sync changeColor() { sync(locker) { synci sasiadow } }
    sync changeState();
    sync getColor();
    sync getState();
    getMyReference();
```    

```
left.getLocker().lock()
right.getLocker().lock()
```