#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#ifndef _HNODE_CLASS_H
#define _HNODE_CLASS_H

using namespace SLDALE003::NODE{

    using namespace std;

    class HuffmanNode{
        public:
            char letter;
            int frequency;
            shared_ptr<HuffmanNode> left;
            shared_ptr<HuffmanNode> right;

            // Default constructor
            HuffmanNode(char l, int f);

            // Destructor
            ~HuffmanNode();

            //Copy Constructor
            HuffmanNode(const HuffmanNode & node);

            //Move Constructor
            HuffmanNode(HuffmanNode && node);

            //Copy Assignment 
            HuffmanNode & operator=(const HuffmanNode & node);

            //Move Assignment
            HuffmanNode & operator=(HuffmanNode && node);
    };

}

#endif