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

namespace SLDALE003{
    
    using namespace std;

    class HuffmanTree{
        private:
            unordered_map<char, int> mapping;

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

    };

}

#endif