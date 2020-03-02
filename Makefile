huffencode: volimage.o
	g++ -o huffencode VolImage.cpp --std=c++11

volimage.o: VolImage.cpp
	g++ -o volimage.o VolImage.cpp --std=c++11

clean: 
	@rm -f *.o *.run

#	./huffencode <inputFile><output file>
run: huffencode
	./huffencode brain_mri_raws/MRI -d 66 67 outputDiffMap