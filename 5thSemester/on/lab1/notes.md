# Lista 1
## Michał Waluś

### Zad. 1

#### Machine Epsilon

```
Float16
Calculated macheps: 0.000977
1 + cal. macheps: 1.001
Macheps: 0.000977

Float32
Calculated macheps: 1.1920929e-7
1 + cal. macheps: 1.0000001
Macheps: 1.1920929e-7

Float64
Calculated macheps: 2.220446049250313e-16
1 + cal. macheps: 1.0000000000000002
Macheps: 2.220446049250313e-16
```

C
```
Float32 macheps: 1.192093e-07
Float64 macheps: 2.220446e-16
```


#### Eta

```
Float16
Calculated eta: 6.0e-8
Eta: 6.0e-8

Float32
Calculated eta: 1.0e-45
Eta: 1.0e-45

Float64
Calculated eta: 5.0e-324
Eta: 5.0e-324
```

#### Jaki związek ma liczba macheps z precyzją arytmetyki?

macheps $= 2 * \epsilon$

#### Jaki związek ma liczba eta z liczbą $MIN_{sub}$?

Są sobie równe.

#### Co zwracają funkcje floatmin(Float32) i floatmin(Float64) i jaki jest związek zwracanych wartości z liczbą $MIN_{nor}$?

```
Float32 floatmin: 1.1754944e-38
Float32 floatmin (bit Representation): 00000000100000000000000000000000

Float64 floatmin: 2.2250738585072014e-308
Float64 floatmin (bit Representation): 0000000000010000000000000000000000000000000000000000000000000000
```

Są równe $MIN_{nor}$.

#### Floatmax

```
Calculated Float16 max: 6.55e4
Float16 max: 6.55e4

Calculated Float32 max: 3.4028235e38
Float32 max: 3.4028235e38

Calculated Float64 max: 1.7976931348623157e308
Float64 max: 1.7976931348623157e308
```

C
```
Float32 max: 3.402823e+38
Float64 max: 1.797693e+308
```

### Zad. 2

```
Float16
Kahan's method: -0.000977
Macheps: 0.000977

Float32
Kahan's method: 1.1920929e-7
Macheps: 1.1920929e-7

Float64
Kahan's method: -2.220446049250313e-16
Macheps: 2.220446049250313e-16
```

### Zad. 3

```
Number of Float64 numbers in [1.0, 2.0): 4503599627370496
Representation of nextfloat(1.0): 0011111111110000000000000000000000000000000000000000000000000001

Number of Float64 numbers in [0.5, 1.0): 4503599627370496
Representation of nextfloat(0.5): 0011111111100000000000000000000000000000000000000000000000000001

Number of Float64 numbers in [2.0, 4.0): 4503599627370496
Representation of nextfloat(2.0): 0100000000000000000000000000000000000000000000000000000000000001
```

W przedziałach [0.5, 1.0] i [2.0, 4.0] liczby są równomiernie rozmieszczone.

Dla (0.5, 1.0): $0.5 + k\delta$ dla $k = 1,\dots,2^{52}-1$ i $\delta = 2^{-53}$

Dla (2.0, 4.0): $2.0 + k\delta$ dla $k = 1,\dots,2^{52}-1$ i $\delta = 2^{-51}$

### Zad. 4

```
x such that x * (1/x) != 1: 1.5000000000000002
Value: 0.9999999999999999
Binary representation: 0011111111111000000000000000000000000000000000000000000000000001

Smallest x such that x * (1/x) != 1: 1.000000057228997
Value: 0.9999999999999999
Binary representation: 0011111111110000000000000000000000001111010111001011111100101010
```

### Zad. 5

```
Float32 forward: -0.4999443
Float32 backward: -0.4543457
Float32 from biggest: -0.5
Float32 from smallest: -0.5

Float64 forward: 1.0251881368296672e-10
Float64 backward: -1.5643308870494366e-10
Float64 from biggest: 0.0
Float64 from smallest: 0.0
```