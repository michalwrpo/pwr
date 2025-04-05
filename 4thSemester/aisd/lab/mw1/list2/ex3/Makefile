CXX := g++
CXX_WARN := -Wall -Wextra

rand:
	$(CXX) $(CXX_WARN) random/genrand.cpp -o rand.out
	$(CXX) $(CXX_WARN) random/genrinc.cpp -o randinc.out
	$(CXX) $(CXX_WARN) random/genrdes.cpp -o randdes.out

merge:
	$(CXX) $(CXX_WARN) mergesort.cpp -o mergesort.out

mysort:
	$(CXX) $(CXX_WARN) mysort.cpp -o mysort.out


clean:
	rm -f *.out