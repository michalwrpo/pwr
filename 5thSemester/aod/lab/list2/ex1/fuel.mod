# Michał Waluś 279695

set I; # airports
set J; # suppliers

param d{i in I}; # demand
param s{j in J}; # supply

param c{i in I, j in J}; # cost

var x{i in I, j in J}, >= 0;

minimize cost: sum{i in I, j in J} c[i,j] * x[i,j];

s.t. supply{j in J}: sum{i in I} x[i,j] <= s[j];
s.t. demand{i in I}: sum{j in J} x[i,j] >= d[i];

solve;

display {i in I, j in J}: x[i,j];
printf 'Total cost = %.2f\n', cost;

end;
