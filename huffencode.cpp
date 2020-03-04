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

    ::SLDALE003::HuffmanTree hTree(map);
    hTree.buildTree();

    return 0;
}