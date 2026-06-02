b=Curve((abs(cos(8 t)))^(A) cos(t)+((1)/(10)) cos(((floor(((8 t)/(π))+((1)/(2))))/(8)) π),(abs(cos(8 t)))^(A) sin(t)+((1)/(10)) sin(((floor(((8 t)/(π))+((1)/(2))))/(8)) π),t,-π,π)

ParametricPlot[{10 * (abs(cos(8t)))^(1/10) cos(t)+ cos(floor(8t/π + 1/2) * π/8), 10 * (abs(cos(8t)))^(1/10) sin(t)+sin(floor(8t/π + 1/2) * π/8)},{t,-π,π}]