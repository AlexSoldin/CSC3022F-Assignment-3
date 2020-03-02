huffencode: huffencode.o
	g++ -o huffencode huffencode.cpp --std=c++11

huffencode.o: huffencode.cpp
	g++ -o huffencode.o huffencode.cpp --std=c++11

clean: 
	@rm -f *.o *.run

#	./huffencode <inputFile><output file>
run: huffencode
	./huffencode inputFile outputFile

test: tests
	g++ -o tester.o tester.cpp --std=c++11
	g++ -o tests tester.cpp --std=c++11
	./tests