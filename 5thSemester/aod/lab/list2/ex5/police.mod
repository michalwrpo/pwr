# Michał Waluś 279695

param n; # number of neighborhoods
param m; # number shifts

set N := (1..n); # neighborhoods
set S := (1..m); # shifts

param minpc{i in N, j in S}; # minimal number of police cars in a given neighborhood and shift
param maxpc{i in N, j in S}; # maximal number of police cars in a given neighborhood and shift

param minn{i in N}; # minimal number of police cars in a given neighborhood
param mins{j in S}; # minimal number of police cars during a given shift

var x{i in N, j in S} >= 0, integer; # number of police cars assigned to a given neighborhood and shift

minimize cars: sum{i in N, j in S} x[i,j];

s.t. minimum{i in N, j in S}: x[i,j] >= minpc[i,j];
s.t. maximum{i in N, j in S}: x[i,j] <= maxpc[i,j];
s.t. neighborhoods{i in N}: sum{j in S} x[i,j] >= minn[i];
s.t. shifts{j in S}: sum{i in N} x[i,j] >= mins[j];

solve;

display x;

printf "Total number of police cars: %d\n", cars;

end;
