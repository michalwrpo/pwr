CXX := g++
CXX_WARN := -Wall -Wextra

rand:
	$(CXX) $(CXX_WARN) random/genrand.cpp -o rand.out
	$(CXX) $(CXX_WARN) random/genrinc.cpp -o randinc.out
	$(CXX) $(CXX_WARN) random/genrdes.cpp -o randdes.out

insort:
	$(CXX) $(CXX_WARN) insort.cpp -o insort.out

quick:
	$(CXX) $(CXX_WARN) quicksort.cpp -o quicksort.out

hybrid:
	$(CXX) $(CXX_WARN) hybridsort.cpp -o hybridsort.out

clean:
	rm -f *.out