CXX := g++
CXX_WARN := -Wall -Wextra

rand:
	$(CXX) $(CXX_WARN) random/genrand.cpp -o rand.out
	$(CXX) $(CXX_WARN) random/genrinc.cpp -o randinc.out
	$(CXX) $(CXX_WARN) random/genrdes.cpp -o randdes.out

dpqs:
	$(CXX) $(CXX_WARN) dpqs.cpp -o dpqs.out

clean:
	rm -f *.out