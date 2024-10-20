# Lista 1

## Zad.1

<p>Zapisz 20 pierwszych liczb naturalnych przy podstawie: 2; 3; 5; 16.</p>

### Base 2

0, 1, 10, 11, 100, 101, 110, 111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111, 10000, 10001, 10010, 10011

### Base 3

0, 1, 2, 10, 11, 12, 20, 21, 22, 100, 101, 102, 110, 111, 112, 120, 121, 122, 200, 201

### Base 5

0, 1, 2, 3, 4, 10, 11, 12, 13, 14, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34

### Base 16

0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, 10, 11, 12, 13

## Zad.2

(11001)<sub>-2</sub> = 1 \* (-2)<sup>0</sup> + 1 \* (-2)<sup>3</sup> + 1 \* (-2)<sup>4</sup> = 1 + (-8) + 16 = 9 

## Zad.3

- 10,10001 = 2,53125
- 101110,0101 = 46,3125
- 1110101,110 = 117,75
- 1101101,111 = 109.875

## Zad.4

1. 225<sub>10</sub> = 1110 0001<sub>2</sub> = 341<sub>8</sub> = E1<sub>16</sub>
2. 1101 0111<sub>2</sub> = 215<sub>10</sub> = 327<sub>8</sub> = D7<sub>16</sub>
3. 623<sub>8</sub> = 403<sub>10</sub> = 1 1001 0011<sub>2</sub> = 193<sub>16</sub>
4. 2ACD<sub>16</sub> = 10957<sub>10</sub> = 10 1010 1100 1101<sub>2</sub> = 25315<sub>8</sub>

## Zad.5 

1. 1230<sub>4</sub> + 23<sub>4</sub> = 1313<sub>4</sub> <br>
1230<sub>4</sub> \* 23 <sub>4</sub> = 31200<sub>4</sub> + 11010<sub>4</sub> = 102210<sub>4</sub>
2. 135,4<sub>6</sub> + 43,2<sub>6</sub> = 223<sub>6</sub> <br>
135,4<sub>6</sub> \* 43,2<sub>6</sub> = 10344<sub>6</sub> + 455<sub>6</sub> + 31,12<sub>6</sub> = 11314,52<sub>6</sub>
3. 367<sub>8</sub> + 715<sub>8</sub> = 1304<sub>8</sub> <br>
367<sub>8</sub> * 715<sub>8</sub> = 330100<sub>8</sub> + 3670<sub>8</sub> + 2323<sub>8</sub> = 336313<sub>8</sub>
4. 296<sub>12</sub> + 57<sub>12</sub> = 331<sub>12</sub> <br>
296<sub>12</sub> * 57<sub>12</sub> = 11B60<sub>12</sub> + 1766<sub>12</sub> = 13706<sub>12</sub>


## Zad. bonus

Zapisac dowolna liczbe przy ujemnej podstawie.

- n<sup>even</sup> = (-n)<sup>even</sup>
- n<sup>odd</sup> = (-n)<sup>odd+1</sup> + (n - 1) \* (-n)<sup>odd</sup>

- overflow on even: n \* (-n)<sup>even</sup> = (-n)<sup>even+2</sup> + (n - 1) \* (-n)<sup>even+1</sup>
- overflow on odd: n \* (-n)<sup>odd</sup> = (-n)<sup>odd+2</sup> + (n - 1) \* (-n)<sup>odd+1</sup>

Patrz bonus1.py