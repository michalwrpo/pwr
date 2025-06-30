# Zadanie dodatkowe - FP
## Michał Waluś

### Funktor

```haskell
instance Functor (CM a) where
    fmap f (CM phi) = CM (phi . (\psi -> psi . f))
```

$f: X \rightarrow Y \\$
Niech $\varphi \in A^{A^X}, \psi \in A^{A^Y} \\$
$F_A(f)(\varphi) = \varphi \circ (\psi \circ f)$.

$\psi \circ f \in A^X$, więc $\varphi \circ (\psi \circ f) \in A^{A^X}$, zatem $F_A(f): F_A(X) \rightarrow F_A(Y)$. 

### Monoidalny

```haskell
instance Monoidal (CM a) where
    unit = CM (\psi -> psi ())
    (CM phi) <:> (CM rho) = CM (\psi -> phi (\x -> rho (\y -> psi (x, y))))
```

$unit \in A^{A^{\{\bullet\}}}$

```haskell
1. unit <:> (CM a φ) = CM (\ψ -> unit (\x -> φ (\y -> ψ (x, y))))  
= CM (\ψ -> (\x -> φ (\y -> ψ (x, y))) () )  
= CM (\ψ -> φ (\y -> ψ ((), y) ) )  
```

### Aplikatywny

```haskell
    instance Applicative (CM a) where
        pure x = CM (\psi -> psi x)
        (CM f) <*> (CM phi) = CM (\psi -> f (\g -> phi (psi . g)))
```