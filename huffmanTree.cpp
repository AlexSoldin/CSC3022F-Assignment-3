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

// namespace SLDALE003{

//     using namespace std;

//     HuffmanTree::HuffmanTree(unordered_map<char, int> map){
//         root = nullptr;
//         mapping = map;
//     }

//     HuffmanTree::~HuffmanTree();

//     HuffmanTree::HuffmanTree(const HuffmanTree & tree);

//     HuffmanTree::HuffmanTree(HuffmanTree && tree);

//     HuffmanTree & HuffmanTree::operator=(const HuffmanTree & tree);

//     HuffmanTree & HuffmanTree::operator=(HuffmanTree && tree);

//     void HuffmanTree::buildTree();

//     void HuffmanTree::insertNode(int i, ::SLDALE003::HuffmanNode l, SLDALE003::HuffmanNode r);

//     void HuffmanTree::buildCodeTable(unordered_map<char, string> &map, shared_ptr<SLDALE003::HuffmanNode> r, string bitString);


// }