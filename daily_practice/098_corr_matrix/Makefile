CPPFLAGS=-std=c++11 -pedantic -Wall -Werror -ggdb3
correl_matrix: main.o asset.o
	g++ -o correl_matrix main.o asset.o
main.o: main.cpp
	g++ $(CPPFLAGS) -c main.cpp
asset.o: asset.cpp asset.hpp
	g++ $(CPPFLAGS) -c asset.cpp

.PHONY: clean
clean:
	rm -f *.o *~ correl_matrix


