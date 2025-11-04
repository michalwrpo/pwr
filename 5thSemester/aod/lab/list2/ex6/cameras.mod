# Michał Waluś 279695

param n; # length
param m; # width
param k; # range of camera

set L := (1..n);
set W := (1..m);

param c{i in L, j in W}; # containers (for all entries should be 0 or 1)

var x{i in L, j in W}, binary; # do we place a camera in the given sqaure

minimize cameras: sum{i in L, j in W} x[i,j];

s.t. no_camera_container{i in L, j in W}: c[i,j] + x[i,j] <= 1; 
s.t. container_observed{i in L, j in W}: 
    c[i,j] 
    - sum{r in (i..n) inter (i..i+k)} x[r, j]
    - sum{r in (1..i) inter (i-k..i)} x[r, j]
    - sum{r in (j..m) inter (j..j+k)} x[i, r]
    - sum{r in (1..j) inter (j-k..j)} x[i, r] <= 0;

solve;

display x;
printf "Cameras: %d\n", cameras;

end;
     