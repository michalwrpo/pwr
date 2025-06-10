import qualified Data.Tree as T hiding (Tree)
 
-- Typy rekurencyjne  

data SimpleTree a = Leaf a | Node (SimpleTree a) (SimpleTree a) deriving (Eq)

instance Show a => Show (SimpleTree a) where
  show (Leaf x)     = "⋖" ++ show x ++ "⋗"
  show (Node t1 t2) = "("++show t1++" △ "++show t2++")"
  
tree1 = Node (Leaf 1) (Node (Leaf 2) (Leaf 3))
tree2 = Node tree1 tree1
tree3 = Node tree2 (Leaf 10)

instance Functor SimpleTree where
  fmap f (Leaf x) = Leaf (f x)
  fmap f (Node t1 t2) = Node (fmap f t1) (fmap f t2)

height :: SimpleTree a -> Int
height (Leaf _)  = 0
height (Node t1 t2) = 1 + max (height t1) (height t2) 

instance Foldable SimpleTree where
  foldMap f (Leaf x) = f x
  foldMap f (Node t1 t2) = 
    (foldMap f t1) <> (foldMap f t2) 