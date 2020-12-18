//
// Created by Sam on 17/12/2020.
//

#ifndef COMPRESSION_HUFFMANTREE_H
#define COMPRESSION_HUFFMANTREE_H


#include <map>
#include "BinaryTree.h"

class HuffmanTree : public BinaryTree
{
public:
	HuffmanTree(char* sortedChars, int size, std::map<char,uint64_t> &frequency);
};


#endif //COMPRESSION_HUFFMANTREE_H
