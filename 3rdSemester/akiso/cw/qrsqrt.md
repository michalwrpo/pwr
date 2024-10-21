```c
float InvSqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return x;
}
```
Original code:
```c
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}
```

1st line:
```c
    float xhalf = 0.5f*x;
```
I think it's pretty obvious, what it does, creates a new variable.

2nd line:
```c
    int i = *(int*)&x;
```
Introduces a new variable which is a cast of x to an int.  

## Float

float x can be written as `x = +-1.b_1b_2b_3... • 2^e_x`, which can be rewritten to `x = +-2^e_x • (1 + m_x)`, where `m_x` is between [0,1).  

float (32 bit) representation

1 bit   | 8 bit     | 23 bits  
sign    | exponent  | significand

sign (S_x): 0 if x is positive, 1 if x is negative  
exponent (E_x): `E_x = e_x + B` is the biased exponent, where B = 127 is the exponent bias (E_x is an unsigned int)
sigificand (M_x): `M_x = m_x • L`, where L = 2^23 

## Log

`x = 2^e_x • (1 + m_x)`  
so  
`log_2(x) = e_x * log_2(1+m_x)`  
we can approximate the log by:  
`log_2(1 + m_x) ~= m_x + s`  
so we can approximate  
`log_2(x) ~= e_x + m_x + s`

Interpreting floating-point bit-pattern of x as an integer I_x gives us:
`I_x = E_xL + M_x = L(e_x + B + m_x) = L(e_x + m_x + s + B - s) ~= Llog_2(x) + L(B-s)`
thus
`log_2(x) = I_x/L - B + s`  
  
Now taking `y = 1/sqrt(x)`  
`log_2(y) = -1/2log_2(x)`
so using the approximation we have 
`I_y/L - B + s ~= -1/2 * (I_x/L - B + s)`  
which implies
`I_y ~=  3/2L(B - s) - 1/2I_x`
where the value of the first part for optimal approximation written in hexadecimal is `0x5f3759df`

We can quickly approximate division of I_x by 2 by moving it one bit to right `i >> 1`

## Newton's method

`f(y) = 1/y^2 - x = 0`
is y_n is an approximation, then a better approximation can be calculated by
`y_(n+1) = y_n - f(y_n)/f'(y_n)`
For our f(y): `y_(n+1) = y_n(3-xy_n^2)/2 = y_n(3/2 - x/2 * y_n^2)`