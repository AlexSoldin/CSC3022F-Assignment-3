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
    for(const char &currentChar : charactersToMap){
        map[currentChar]++;
    }

    /* Check contents of map */
    // cout << "Contents of Map\n-----------------\n";
    // for (auto & instance : map){
	// cout << instance.first << ": " << instance.second << endl; 
    // }
    cout << "\n";

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
        outputBuffer += mapToCompress[currentChar];
    }
    hTree.writeCodeTableToFile(mapToCompress, outputBuffer, outputFile, outputPath);

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
    int numberOfBitsOut = numberOfBytes * 8;
    compressedOutputFile.close();

    ofstream compressedOutputHeader(outputPath+outputFile+"Compressed.hdr",ios::binary);
    compressedOutputHeader << numberOfBitsOut;
    compressedOutputHeader.close();

    double goodCompression = hTree.returnRatio(numberOfBytes, charactersToMap.size());
    cout << "Compression Ratio With Bit Packing is: " << goodCompression << "\n\n";

    cout << "Improvement of using Bit Packing is: " << badCompression/goodCompression << "x\n\n"; 

    /* Extra Credit - Part 2 */
    ifstream compressedInputHeader(outputPath+outputFile+"Compressed.hdr");
    int numberOfBitsIn;
    compressedInputHeader >> numberOfBitsIn;
    compressedInputHeader.close();

    ifstream compressedInputFile(outputPath+outputFile+"Compressed.txt");
    string inputBuffer;
    compressedInputFile >> inputBuffer;
    compressedInputFile.close();

    bitset<8> Byte;
    string resultBitString;
    string tempBitString;

    i = 0;
    while(i < numberOfBitsIn/8){
        Byte = inputBuffer[i];
        tempBitString = Byte.to_string();
        string UndoBitPacking;
        for(int j = tempBitString.length()-1; j >= 0; j--){
            UndoBitPacking+=tempBitString[j];
        }
        resultBitString+=UndoBitPacking;
        i++;
    }

    ofstream matching(outputPath+"UnpackedCompressedOutput.txt", ios::binary);
    matching << resultBitString;
    matching.close();

    return 0;
}
