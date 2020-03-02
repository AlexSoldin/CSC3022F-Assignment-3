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

namespace SLDALE003::TREE{
    
    using namespace std;

    class HuffmanTree{
        private:
            unordered_map<char, int> map;
            priority_queue<SLDALE003::NODE::huffmanNode> root;

        public:

        

    }

}

#endif