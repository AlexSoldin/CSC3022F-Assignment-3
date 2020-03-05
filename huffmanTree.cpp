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
            SLDALE003::HuffmanNode node(instance.first, instance.second);
            myQueue.push(node);
        }

        while(myQueue.size()!=1){
            SLDALE003::HuffmanNode l = myQueue.top();
            myQueue.pop();

            SLDALE003::HuffmanNode r = myQueue.top();
            myQueue.pop();

            int combinedFrequency = l.frequency + r.frequency;
            insertNode(combinedFrequency, l, r);
        }

        SLDALE003::HuffmanNode rootNode = myQueue.top();
        myQueue.pop();
        root = make_shared<SLDALE003::HuffmanNode>(rootNode);
    }

    void HuffmanTree::insertNode(int i, SLDALE003::HuffmanNode l, SLDALE003::HuffmanNode r){
        SLDALE003::HuffmanNode toAddNode(0,i);
        toAddNode.left = make_shared<SLDALE003::HuffmanNode> (l);
        toAddNode.right = make_shared<SLDALE003::HuffmanNode> (r);
        myQueue.push(toAddNode);
    }

    void HuffmanTree::buildCodeTable(unordered_map<char, string> &map, shared_ptr<SLDALE003::HuffmanNode> r, string bitString){
        string outputString = bitString;

        if((*r).letter!=0){
            char character = (*r).letter;
            map[character] = outputString;
        }
        else{
            buildCodeTable(map, (*r).left, outputString+"0");
            buildCodeTable(map, (*r).right, outputString+"1");
        }
    }

    void HuffmanTree::writeCodeTableToFile(unordered_map<char, string> map, string outputBuffer, string outputFileName){
        string path = "./Output/";
        ofstream outputFile(path+outputFileName,ios::binary);
        const char* bytes = outputBuffer.c_str();
        outputFile.write(bytes, outputBuffer.length());
        outputFile.close();

        ofstream outputHeaderFile(path+outputFileName+".hdr");
        outputHeaderFile << map.size() << "\n";
        for(auto & instance: map){
            outputHeaderFile << instance.first << " " << instance.second << "\n";
        }
        outputHeaderFile.close();
    }

    double HuffmanTree::returnRatio(int size1, int size2){
        double ratio = double(size1)/double(size2);
        return ratio;
    }

}