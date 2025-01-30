import random as rnd


if __name__=="__main__":
    file = open("ex3.txt", 'w')
    
    v = [-1, 1]
    for n in range(3):
        N = 10**(n+2)
        k = 5000
        for i in range(k):
            S = 0
            L = 0
            for j in range(N):
                X = rnd.choice(v)
                if S > 0:
                    L += 1
                    S += X
                else:
                    S += X
                    if S > 0:
                        L += 1
            file.write(str(N) + " " + str(L/N) + "\n")
            print(N, i, S, L)

    file.close()