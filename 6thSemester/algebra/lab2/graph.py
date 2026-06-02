import matplotlib.pyplot as mpl
from mpmath import mp

mp.dps = 50
A = 4.85
B = 1.1
C = mp.mpf('1/20')

def x(t):
    base = mp.cos(t) * mp.power(abs(mp.cos(8 * t)), C)
    
    shift = mp.cos(mp.floor(8 * t / mp.pi + mp.mpf('1/2')) * mp.pi / 8)
    
    return A * base + B * shift

def y(t):
    base = mp.sin(t) * mp.power(abs(mp.cos(8 * t)), C)
    shift = mp.sin(mp.floor(8 * t / mp.pi + mp.mpf('1/2')) * mp.pi / 8)

    return A * base + B * shift

if __name__ == "__main__":
    pi = mp.pi
    limit = 50
    granularity = 10
    
    for i in range(0, 16):        
        base_left = (2*i-1) * pi / 16
        base_right = (2*i+1) * pi / 16

        t_list = [(base_left + mp.power(10, -k/granularity)) for k in range(5 * granularity, limit * granularity)]
            
        start_mid = base_left + mp.mpf('1e-5')
        end_mid = base_right - mp.mpf('1e-5')
        t_list.extend(mp.linspace(start_mid, end_mid, 1000))
        
        t_list.extend([base_right - mp.power(10, -k/granularity) for k in range(5 * granularity, limit * granularity)])
            
        xvalues = [x(ti) for ti in t_list]
        yvalues = [y(ti) for ti in t_list]
        
        mpl.fill([float(xv) for xv in xvalues], [float(yv) for yv in yvalues], color="#ad842c")

    r = 0.8

    mpl.fill([r * mp.cos(ti) for ti in mp.linspace(0, 2 * pi, 1000)], [r * mp.sin(ti) for ti in mp.linspace(0, 2 * pi, 1000)], color="#ad842c")
    
    mpl.gca().set_facecolor("#940409")
    mpl.gca().set_aspect('equal', adjustable='box')
    mpl.show()