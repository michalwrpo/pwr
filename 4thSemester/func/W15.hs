seg3 (mx, my, mz) = do x <- mx
                       y <- my
                       z <- mz
                       return ([x, y, z])

-- seq3 (ma, ma, ma) -> m ([a, a, a])
-- sequence [ma] -> m [a] 

-- seq3_ = do mx
--             my
--             mz
--             return ()

-- sequence_ = m ()