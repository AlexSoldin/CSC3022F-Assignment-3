#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <unordered_map>
#include <queue>
#include <memory>

#include "huffmanTree.h"

namespace SLDALE003{

    using namespace std;

    HuffmanTree::HuffmanTree(unordered_map<char, int> map){
        root = nullptr;
        mapping = map;
    }

    HuffmanTree::~HuffmanTree(){
        root = nullptr;
    }

    HuffmanTree::HuffmanTree(const HuffmanTree & tree): mapping(tree.mapping), root(tree.root), myQueue(tree.myQueue){};

    HuffmanTree::HuffmanTree(HuffmanTree && tree): mapping(move(tree.mapping)), root(move(tree.root)), myQueue(move(tree.myQueue)){};

//     HuffmanTree & HuffmanTree::operator=(const HuffmanTree & tree);

//     HuffmanTree & HuffmanTree::operator=(HuffmanTree && tree);

//     void HuffmanTree::buildTree();

//     void HuffmanTree::insertNode(int i, ::SLDALE003::HuffmanNode l, SLDALE003::HuffmanNode r);

//     void HuffmanTree::buildCodeTable(unordered_map<char, string> &map, shared_ptr<SLDALE003::HuffmanNode> r, string bitString);


}