huffencode.run: huffencode.o
	g++ -o huffencode.run huffencode.cpp --std=c++11

huffencode.o: huffencode.cpp
	g++ -o huffencode.o huffencode.cpp --std=c++11

clean: 
	@rm -f *.o *.run

#	./huffencode <inputFile><output file>
run: huffencode.run
	./huffencode inputFileExample.txt outputFileExample.txt

test: tests.run
	g++ -o tester.o tester.cpp --std=c++11
	g++ -o tests.run tester.cpp --std=c++11
	./tests