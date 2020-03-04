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
// #include "catch.hpp"

using namespace std;

int main(int argc, char * argv[]){
    string inputFile = argv[1];
    string outputFile = argv[2];

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
    cout << "Contents of Map\n-----------------\n";
    for (auto & instance : map){
        cout << instance.first << ": " << instance.second << endl; 
    }
    cout << "\n";

    ::SLDALE003::HuffmanTree hTree(map);
    hTree.buildTree();
    cout << "Huffman Tree Build Successful\n\n";

    unordered_map<char, string> mapToCompress;
    hTree.buildCodeTable(mapToCompress, hTree.root, "");
    cout << "Code Table Build Successful\n\n";

    /* Check contents of map */
    cout << "Contents of Map to Compress\n---------------------------\n";
    for (auto & instance : mapToCompress){
        cout << "Character: " <<instance.first << " has bit string: " << instance.second << endl; 
    }
    cout << "\n";

    return 0;
}