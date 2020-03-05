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
#include <memory>

#include "huffmanNode.h"

#ifndef _HTREE_CLASS_H
#define _HTREE_CLASS_H

struct compareFrequency{
    bool operator() (const SLDALE003::HuffmanNode& node1, const SLDALE003::HuffmanNode& node2){
        return node1.frequency > node2.frequency;
    }
};

namespace SLDALE003{
    
    using namespace std;

    class HuffmanTree{
        private:
            unordered_map<char, int> mapping;
            priority_queue<::SLDALE003::HuffmanNode, vector<::SLDALE003::HuffmanNode>,::compareFrequency> myQueue;

        public:
            shared_ptr<::SLDALE003::HuffmanNode> root;

            //Default Constructor
            HuffmanTree(unordered_map<char, int> map);

            //Destructor 
            ~HuffmanTree();

            //Copy Constructor
            HuffmanTree(const HuffmanTree & tree);

            //Move Constructor
            HuffmanTree(HuffmanTree && tree);

            //Copy Assignment Operator
            HuffmanTree & operator=(const HuffmanTree & tree);

            //Move Assignment Operator
            HuffmanTree & operator=(HuffmanTree && tree);

            void buildTree();

            void insertNode(int i, ::SLDALE003::HuffmanNode l, ::SLDALE003::HuffmanNode r);
            
            void buildCodeTable(unordered_map<char, string> &map, shared_ptr<::SLDALE003::HuffmanNode> r, string bitString);

            void writeCodeTableToFile(unordered_map<char, string> map, string outputBuffer, string outputFile);
    };

}

#endif