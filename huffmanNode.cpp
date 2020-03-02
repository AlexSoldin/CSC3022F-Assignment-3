#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#include "huffmanNode.h"

namespace SLDALE003::NODE{
    
    using namespace std;

   HuffmanNode(char l, int f){
        letter = l;
        frequency = f;
    }

    ~HuffmanNode(){}

    HuffmanNode(const HuffmanNode & node): 
        letter(node.letter), freq(node.freq), 
        left(node.left), right(node.right){} 

    /*  
        Connects the pointer to the new object
        Nulls the old connections
    */
    HuffmanNode(HuffmanNode && node):
        letter(move(node.letter)), freq(move(node.freq)), 
        left(move(node.left)), right(move(node.right)){
            node.letter = 0;
            node.frequency = 0;
        } 

    HuffmanNode & operator=(const HuffmanNode & node){
        letter = node.letter;
        frequency = node.frequency;
        left = nullptr;
        left = node.left;
        right = nullptr;
        right = node.right;
        return *this;
    }

    HuffmanNode & operator=(HuffmanNode && node){
        letter = node.letter;
        frequency = node.frequency;
        left = nullptr;
        left = move(node.left);
        right = nullptr;
        right = move(node.right);
        node.letter = 0;
        node.frequency = 0;
        return *this;
    }


}