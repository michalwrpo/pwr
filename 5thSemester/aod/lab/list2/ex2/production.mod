# Michał Waluś 279695

param n; # number of products
param m; # number of machines

set I := (1..n); # products
set J := (1..m); # machines

param a{j in J}; # availability of jth machine (in hours per week)
param cm{j in J}; # cost of jth machine's hour of work (in dollars) 
param p{i in I}; # sell price of ith product (in dollars per kg)
param cp{i in I}; # cost of materials for ith product (in dollars per kg)

param d{i in I}; # demand of ith product (in kg per week)

param t{i in I, j in J}; # time on jth machine required to produce 1kg of ith product (in minutes) 

var x{i in I}, >= 0; # amount of ith product produced (in kg per week)

maximize profit: sum{i in I} x[i] * (p[i] - cp[i] - (sum{j in J} cm[j] * t[i,j] / 60));

s.t. time{j in J}: sum{i in I} x[i] * t[i,j] <= 60 * a[j];
s.t. everything_sells{i in I}: x[i] <= d[i];

solve;

display{i in I}: x[i];
printf "Profit: $%.2f\n", profit;

end;
