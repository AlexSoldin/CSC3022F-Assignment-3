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

    HuffmanTree & HuffmanTree::operator=(const HuffmanTree & tree){
        mapping = tree.mapping;
        myQueue = tree.myQueue;
        root = nullptr;
        root = tree.root;
        return *this;
    }

    HuffmanTree & HuffmanTree::operator=(HuffmanTree && tree){
        mapping = move(tree.mapping);
        myQueue = move(tree.myQueue);
        root = nullptr;
        root = move(tree.root);
        return *this;
    }

    void HuffmanTree::buildTree(){
        for (auto & instance : mapping){
            ::SLDALE003::HuffmanNode node(instance.first, instance.second);
            myQueue.push(node);
        }

        while(myQueue.size()>1){
            ::SLDALE003::HuffmanNode l = myQueue.top();
            myQueue.pop();
            ::SLDALE003::HuffmanNode r = myQueue.top();
            myQueue.pop();
            int combinedFrequency = l.frequency + r.frequency;
            insertNode(combinedFrequency, l, r);
        }

        ::SLDALE003::HuffmanNode rootNode = myQueue.top();
        myQueue.pop();
        root = make_shared<::SLDALE003::HuffmanNode>(rootNode);
    }

    void HuffmanTree::insertNode(int i, ::SLDALE003::HuffmanNode l, SLDALE003::HuffmanNode r){
        ::SLDALE003::HuffmanNode toAddNode(0,i);
        toAddNode.left = make_shared<::SLDALE003::HuffmanNode> (l);
        toAddNode.right = make_shared<::SLDALE003::HuffmanNode> (r);
        myQueue.push(toAddNode);
    }

//     void HuffmanTree::buildCodeTable(unordered_map<char, string> &map, shared_ptr<SLDALE003::HuffmanNode> r, string bitString);


}