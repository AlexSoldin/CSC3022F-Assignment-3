huffencode: huffencode.o
	g++ -o huffencode huffencode.cpp --std=c++11

huffencode.o: huffencode.cpp
	g++ -o huffencode.o huffencode.cpp --std=c++11

clean: 
	@rm -f *.o huffencode tests

#	./huffencode <inputFile><output file>
run: huffencode
	./huffencode inputFileExample.txt outputFileExample.txt

test: tests
	g++ -o tests.o tests.cpp --std=c++11
	g++ -o tests tests.cpp --std=c++11
	./tests