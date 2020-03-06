#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>
#include <unordered_map>
#include <queue>
#include <bitset>

#include "huffmanNode.cpp"
#include "huffmanTree.cpp"

using namespace std;

int main(int argc, char * argv[]){
    string inputFile = argv[1];
    string outputFile = argv[2];
    string outputPath = "./Output/";

    ifstream input(inputFile);
    char currentChar;
    vector<char> charactersToMap;

    while(!input.eof()){
        input >> currentChar >> noskipws;
        charactersToMap.push_back(currentChar);
    }
    input.close();

    unordered_map<char, int> map;
    for(const char &currentChar: charactersToMap){
        map[currentChar]++;
    }

    /* Check contents of map */
    // cout << "Contents of Map\n-----------------\n";
    // for (auto & instance : map){
	// cout << instance.first << ": " << instance.second << endl; 
    // }
    //cout << "\n";

    ::SLDALE003::HuffmanTree hTree(map);
    hTree.buildTree();
    cout << "Huffman Tree Build Successful\n\n";

    unordered_map<char, string> mapToCompress;
    hTree.buildCodeTable(mapToCompress, hTree.root, "");
    cout << "Code Table Build Successful\n\n";

    /* Check contents of map */
    // cout << "Bit Strings to Compress\n-------------------------------------\n";
    // for (auto & instance : mapToCompress){
    //     cout << "Character: " <<instance.first << " has bit string: " << instance.second << endl; 
    // }
    cout << "\n";

    string outputBuffer = "";
    for(const char &currentChar : charactersToMap){
        outputBuffer+=mapToCompress[currentChar];
    }
    hTree.writeCodeTableToFile(mapToCompress, outputBuffer, outputFile);


    double badCompression = hTree.returnRatio(outputBuffer.length(), charactersToMap.size());
    cout << "Compression Ratio Without Bit Packing is: " << badCompression << "\n\n";

    /* Extra Credit - Part 1 */
    int bufferLength = outputBuffer.length();
    ofstream compressedOutputFile(outputPath+outputFile+"Compressed.txt",ios::binary);
    
    int i = 0;
    while(i<bufferLength){

        char byte = 0;
        string bits = "";

        if(i+8 < bufferLength){
            bits = outputBuffer.substr(i, i+8);
        }
        else{
            bits = outputBuffer.substr(i, bufferLength);
        }

        for(int count = 0; count < 8; count++){
            if(count < bits.length()){
                byte |= (bits[count] & 1) << count;
            }
            else{
                byte |= 1 << count;
            }
        }
        compressedOutputFile.put(byte);
        i+=8;
    }

    int pos = compressedOutputFile.tellp(); //returns the current “put” position of the pointer in the stream
    int numberOfBytes = pos + 1;
    int numberOfBits = numberOfBytes * 8;
    compressedOutputFile.close();

    ofstream compressedOutputHeader(outputPath+outputFile+"Compressed.hdr",ios::binary);
    compressedOutputHeader << numberOfBits;
    compressedOutputHeader.close();

    double goodCompression = hTree.returnRatio(numberOfBytes, charactersToMap.size());
    cout << "Compression Ratio With Bit Packing is: " << goodCompression << "\n\n";

    cout << "This is " << badCompression/goodCompression << "x better than before\n\n"; 

    /* Extra Credit - Part 2 */
    ifstream compressedInputHeader(outputFile+"Compressed.hdr");



    return 0;
}
