//
// Created by Sam Collier on 24/11/2020.
//

#ifndef BINARYSEARCHTREE_BINARYTREE_H
#define BINARYSEARCHTREE_BINARYTREE_H


#include "Node.h"
#include <vector>
#include <cmath>

class BinaryTree
{
	Node* insertRecursive(Node* rootNode, int key);
    Node* search(Node* rootNode, int key);
    Node* removeRecursive(Node* rootNode, int key);
    int minimumValue(Node* rootNode);
    void toStringRecursive(Node* rootNode,int numSpaces,std::vector<std::string> &output);
    int heightRecursive(Node* rootNode);
public:
	Node* root=nullptr;
    int height();
	void insert(int key);
	Node* search(int key);
	Node* remove(int key);
	std::string toString();
};


#endif //BINARYSEARCHTREE_BINARYTREE_H
