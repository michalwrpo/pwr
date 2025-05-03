CXX := g++
CXX_WARN := -Wall -Wextra

rand:
	$(CXX) $(CXX_WARN) random/genrand.cpp -o rand.out
	$(CXX) $(CXX_WARN) random/genrinc.cpp -o randinc.out
	$(CXX) $(CXX_WARN) random/genrdes.cpp -o randdes.out

rselect:
	$(CXX) $(CXX_WARN) randomselect.cpp -o randomselect.out

select:
	$(CXX) $(CXX_WARN) select.cpp -o select.out


clean:
	rm -f *.out