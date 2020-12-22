//
// Created by Sam on 17/12/2020.
//

#ifndef COMPRESSION_HUFFMANTREE_H
#define COMPRESSION_HUFFMANTREE_H


#include <map>
#include "BinaryTree.h"

class HuffmanTree : public BinaryTree
{
	std::map<char,uint64_t> map;
	void readFileRecursive(Node* &node, FILE* fp);
public:
	HuffmanTree(char* sortedChars, int size, std::map<char,uint64_t> &frequency);
	HuffmanTree(const std::string& fileName);
	void saveToFile(int extraBits, const std::string& fileName);
};


#endif //COMPRESSION_HUFFMANTREE_H
