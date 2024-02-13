CPPFLAGS=-std=c++11 -pedantic -Wall -Werror -ggdb3
efficient_frontier: main.o asset.o
	g++ -o efficient_frontier main.o asset.o
main.o: main.cpp matrix_cal.cpp
	g++ $(CPPFLAGS) -c main.cpp
asset.o: asset.cpp asset.hpp
	g++ $(CPPFLAGS) -c asset.cpp

.PHONY: clean
clean:
	rm -f *.o *~ efficient_frontier