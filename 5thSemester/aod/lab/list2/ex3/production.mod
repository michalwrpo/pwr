# Michał Waluś 279695

param K; # number of periods

set J := (1..K); # periods
set J0 := (0..K); # set J with 0  

param l{j in J}; # maximal amount (limit) of product that can be produced in jth period;
param c{j in J}; # cost of producing 1 unit of product in jth period
param a{j in J}; # number of products that can be produced above limit in jth period
param o{j in J}; # cost of producting 1 unit above limit in jth period
param d{j in J}; # demand for product in jth period

param s{j in J}; # amount of units of product that can be stored after jth period
param sc{j in J}; # cost of storing 1 unit after jth period

param b; # amount that is stored at the beginning
param e; # amount that has to be stored at the end

var x{j in J} >= 0; # amount that will be produced in jth period
var y{j in J} >= 0; # amount that will be produced above limit in jth period

var sur{j in J0} >= 0; # amount remaining over demand in jth period

minimize cost: sum{j in J} (x[j] * c[j] + y[j] * o[j] + sur[j] * sc[j]);

s.t. demand{j in J}: x[j] + y[j] + sur[j-1] >= d[j];

s.t. surplus{j in J}: x[j] + y[j] + sur[j-1] - d[j] = sur[j];
s.t. surplus_start: sur[0] = b;
s.t. surplus_end: sur[K] = e;

s.t. legal_production{j in J}: x[j] <= l[j];
s.t. legal_over_production{j in J}: y[j] <= a[j];
s.t. legal_surplus{j in J}: sur[j] <= s[j];

solve;

display{j in J}: x[j];
display{j in J}: y[j];
display{j in J}: sur[j];
printf "Total cost: $%.2f\n", cost;

end;
