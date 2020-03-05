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
    ifstream input1("test1.txt");
    char character1;
    vector<char> charactersToMap1;

    while(!input1.eof()){
        input1 >> character1 >> noskipws;
        charactersToMap1.push_back(character1);
    }
    input1.close();

    unordered_map<char, int> map1;
    for(const char &c: charactersToMap1){
        map1[c]++;
    }

    ifstream input2("test2.txt");
    char character2;
    vector<char> charactersToMap2;

    while(!input2.eof()){
        input2 >> character2 >> noskipws;
        charactersToMap2.push_back(character2);
    }
    input2.close();

    unordered_map<char, int> map2;
    for(const char &c: charactersToMap2){
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

        for(auto & instance: map2){
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

}