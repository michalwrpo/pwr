CXX := gcc
CXX_WARN := -Wall -Wextra -Wpedantic 

experiment:
	$(CXX) $(CXX_WARN) experiment.c binHeap.c mtwister.c -o exp.out

data:
	$(CXX) $(CXX_WARN) data.c binHeap.c mtwister.c -o data.out

clean:
	rm -f *.out