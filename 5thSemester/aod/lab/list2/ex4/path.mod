# Michał Waluś 279695

param n; # number of cities

set N := (1..n); # cities (nodes)
set A within {i in N, j in N}; # roads between cities (arcs)

param start_city; # city in which we start
param end_city; # city in which we end

param c{i in N, j in N}; # cost of traveling along some arc
param t{i in N, j in N}; # travel time of a road

param T; # time cap

var x{(i,j) in A}, binary; # do we choose an edge or not

minimize cost: sum{(i,j) in A} x[i,j] * c[i,j];

s.t. travel_time: sum{(i,j) in A} x[i,j] * t[i,j] <= T;
s.t. exists_first: sum{(start_city, j) in A} x[start_city,j] = 1;
s.t. enters_last: sum{(i, end_city) in A} x[i, end_city] = 1;  
s.t. exists_middle_notes{i in (N diff {start_city, end_city})}: sum{(j, i) in A} x[j,i] = sum{(i, j) in A} x[i,j];

solve;

display x;

printf "Total cost: %d\n", cost;
printf "Travel time: %d\n", travel_time;

end;