all:	main.cpp Vector.h
	g++ -std=c++11 -g -o test main.cpp -O3
clean:	test
	rm -f test