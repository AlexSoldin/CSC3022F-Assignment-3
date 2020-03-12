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

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Methods Perform as Expected for Two Separate Test Files", "[ASSIGNMENT]"){
    ifstream input1("./TestFiles/test1.txt");
    char character1;
    vector<char> charactersToMap1;

    while(!input1.eof()){
        input1 >> character1 >> noskipws;
        charactersToMap1.push_back(character1);
    }
    input1.close();

    unordered_map<char, int> map1;
    for(const char &c : charactersToMap1){
        map1[c]++;
    }

    ifstream input2("./TestFiles/test2.txt");
    char character2;
    vector<char> charactersToMap2;

    while(!input2.eof()){
        input2 >> character2 >> noskipws;
        charactersToMap2.push_back(character2);
    }
    input2.close();

    unordered_map<char, int> map2;
    for(const char &c : charactersToMap2){
        map2[c]++;
    }

    SECTION("Map is Created with Correct Character Frequencies"){
        REQUIRE(map1['H']==1);
        REQUIRE(map1['x']==0);
        REQUIRE(map1['l']==3);
        REQUIRE(map1[' ']==1);
        REQUIRE(map1['!']==1);
        REQUIRE(map1['o']==2);

        REQUIRE(map2['t']==4);
        REQUIRE(map2['o']==5);
        REQUIRE(map2['l']==0);
        REQUIRE(map2[' ']==7);
        REQUIRE(map2['x']==0);
        REQUIRE(map2['i']==2);
    }

    ::SLDALE003::HuffmanTree hTree1(map1);
    hTree1.buildTree();
    ::SLDALE003::HuffmanTree hTree2(map2);
    hTree2.buildTree();

    SECTION("Tree is Created Correctly. Sum of Root = Sum of Frequencies in Map"){
        int frequencyCount1 = 0;
        int frequencyCount2 = 0;

        for(auto & instance : map1){
            frequencyCount1 += instance.second;
        }

        for(auto & instance : map2){
            frequencyCount2 += instance.second;
        }

        REQUIRE(((*hTree1.root)).frequency == frequencyCount1);
        REQUIRE(((*hTree2.root)).frequency == frequencyCount2);
    }

    unordered_map<char, string> mapToCompress1;
    hTree1.buildCodeTable(mapToCompress1, hTree1.root, "");
    unordered_map<char, string> mapToCompress2;
    hTree2.buildCodeTable(mapToCompress2, hTree2.root, "");
    
    SECTION("Tree Delegates the Correct Bit String According to Frequency (Smallest Bit String for Most Common Value)"){
        bool check11 = (mapToCompress1['l']).find('1')!=string::npos;
        bool check12 = (mapToCompress1['o']).find('1')!=string::npos;
        REQUIRE(check11 == 0);
        REQUIRE(check12 == 1);
        REQUIRE(mapToCompress1['x']=="");

        bool check21 = (mapToCompress2['o']).find('1')!=string::npos;
        REQUIRE(check21 == 1);
        REQUIRE(mapToCompress2['q']=="");
    }

    string outputBuffer1 = "";
    for(const char &c : charactersToMap1){
        outputBuffer1 += mapToCompress1[c];
    }
    hTree1.writeCodeTableToFile(mapToCompress1, outputBuffer1, "test1_Output", "./TestOutput/");

    string outputBuffer2 = "";
    for(const char &c : charactersToMap2){
        outputBuffer2 += mapToCompress2[c];
    }
    hTree2.writeCodeTableToFile(mapToCompress2, outputBuffer2, "test2_Output", "./TestOutput/");

    SECTION("Check that Order of Encoded File is the same as the Order of the Input File (Can be Extended to Entire File)"){
        char char1 = charactersToMap1[0];
        string firstCode = mapToCompress1[char1];
        string value1;
        ifstream inputFile1("./TestOutput/test1_Output.txt");
        inputFile1 >> value1;
        inputFile1.close();
        string test1String = value1.substr(0, firstCode.length());
        int test1Integer = firstCode.compare(test1String); 
        REQUIRE(test1Integer == 0); //0 indicates equality

        char char2 = charactersToMap2[0];
        string secondCode = mapToCompress2[char2];
        string value2;
        ifstream inputFile2("./TestOutput/test2_Output.txt");
        inputFile2 >> value2;
        inputFile2.close();
        string test2String = value2.substr(0, secondCode.length());
        int test2Integer = secondCode.compare(test2String); 
        REQUIRE(test2Integer == 0); //0 indicates equality
    }

    int bufferLength = outputBuffer1.length();
    ofstream compressedOutputFile("./TestOutput/test1_Output_Compressed.txt",ios::binary);
    
    int i = 0;
    while(i<bufferLength){

        char byte = 0;
        string bits = "";

        if(i+8 < bufferLength){
            bits = outputBuffer1.substr(i, i+8);
        }
        else{
            bits = outputBuffer1.substr(i, bufferLength);
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

    ofstream compressedOutputHeader("./TestOutput/test1_Output_Compressed.hdr",ios::binary);
    compressedOutputHeader << numberOfBitsOut;
    compressedOutputHeader.close();

    SECTION("Check that Bit Packed Output File is Actually Smaller than Original Input File and Enconded File"){
        int sizeOfInput = charactersToMap1.size();
        int sizeOfEncoded = outputBuffer1.length();
        int sizeOfBitPacked = numberOfBytes;

        REQUIRE(sizeOfBitPacked < sizeOfInput);
        REQUIRE(sizeOfBitPacked < sizeOfEncoded);
    }

    ifstream compressedInputHeader("./TestOutput/test1_Output_Compressed.hdr");
    int numberOfBitsIn;
    compressedInputHeader >> numberOfBitsIn;
    compressedInputHeader.close();

    ifstream compressedInputFile("./TestOutput/test1_Output_Compressed.txt");
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

    ofstream matching("./TestOutput/UnpackedCompressedOutput.txt", ios::binary);
    matching << resultBitString;
    matching.close();

    SECTION("Bit Unpacking File is the Same Size as Original Encoded File"){
        int lengthEncoded = numberOfBitsOut;
        int legnthUnpacked = resultBitString.length();

        REQUIRE(lengthEncoded == legnthUnpacked);
    }



}