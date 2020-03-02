#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#include "huffmanNode.h"

namespace SLDALE003{
    using namespace std;

    HuffmanNode::HuffmanNode(char l, int f){
            letter = l;
            frequency = f;
        }

    HuffmanNode::~HuffmanNode(){}

    HuffmanNode::HuffmanNode(const HuffmanNode & node): letter(node.letter), frequency(node.frequency), left(node.left), right(node.right){} 

    /*  
        Connects the pointer to the new object
        Nulls the old connections
    */
    HuffmanNode::HuffmanNode(HuffmanNode && node): letter(move(node.letter)), frequency(move(node.frequency)), left(move(node.left)), right(move(node.right)){
            node.letter = 0;
            node.frequency = 0;
        } 

    HuffmanNode & HuffmanNode::operator=(const HuffmanNode & node){
        letter = node.letter;
        frequency = node.frequency;
        left = nullptr;
        left = node.left;
        right = nullptr;
        right = node.right;
        return *this;
    }

    HuffmanNode & HuffmanNode::operator=(HuffmanNode && node){
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