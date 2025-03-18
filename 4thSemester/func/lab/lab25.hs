qs [] = []
qs (x:xs) = qs [t| t <- xs, t<=x] ++ [x] ++ qs [t|t <- xs, t>x]

qS [] = []
qS [x] = [x]
qS (x:xs) = qS [t| t <- xs, t<=x] ++ x:qS [t|t <- xs, t>x]