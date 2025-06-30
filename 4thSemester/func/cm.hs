module CM where
    import Control.Applicative 

    class Functor f => Monoidal f where
        unit :: f ()
        (<:>) :: f a -> f b -> f (a,b) 

    data CM a x = CM ( (x->a) -> a)

    instance Functor (CM a) where
        fmap f (CM phi) = CM (phi . (\psi -> psi . f))

    instance Monoidal (CM a) where
        unit = CM (\psi -> psi ())
        (CM phi) <:> (CM rho) = CM (\psi -> phi (\x -> rho (\y -> psi (x, y))))

    instance Applicative (CM a) where
        pure x = CM (\psi -> psi x)
        (CM f) <*> (CM phi) = CM (\psi -> f (\g -> phi (psi . g)))