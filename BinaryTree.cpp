//
// Created by Sam Collier on 24/11/2020.
//

#include "BinaryTree.h"

void BinaryTree::insert(int key)
{
	root=insertRecursive(root,key);
}

Node* BinaryTree::insertRecursive(Node* rootNode, int key)
{
	//base case
	if(rootNode == nullptr)
	{
        rootNode = new Node(key);
		return rootNode;
	}
	// if key is less than root, go left
	else if(key < rootNode->getKey())
	{
		rootNode->setLeft(insertRecursive(rootNode->getLeft(), key));
	}
	// if key is greater than root, go right.
	else if(key > rootNode->getKey())
	{
		rootNode->setRight(insertRecursive(rootNode->getRight(), key));
	}
	return rootNode;
}

Node* BinaryTree::search(Node* rootNode, int key)
{
	if(rootNode->getKey() == key)
		return rootNode;
	else if(key > rootNode->getKey())
		return search(rootNode->getRight(), key);
	else if(key < rootNode->getKey())
		return search(rootNode->getLeft(), key);
	return nullptr;
}

Node* BinaryTree::search(int key)
{
    return search(root,key);
}

Node* BinaryTree::removeRecursive(Node* rootNode, int key)
{
    // base case
    if(rootNode==nullptr)return rootNode;

    if(key < rootNode->getKey()) // key is smaller, so look left
        rootNode->setLeft(removeRecursive(rootNode->getLeft(),key));
    else if(key > rootNode->getKey()) // key is greater, so look right
        rootNode->setRight(removeRecursive(rootNode->getRight(),key));
    else // key is equal to root, so we have found what we are looking for
    {
        // if we have one child
        if(rootNode->getLeft()==nullptr)
        {
            Node* tmp = rootNode->getRight();
            delete rootNode;
            return tmp;
        }
        else if(rootNode->getRight()==nullptr)
        {
            Node* tmp = rootNode->getLeft();
            delete rootNode;
            return tmp;
        }

        // if we have two children
        // set the node to the smallest value on the right side.
        Node* tmp = search(rootNode->getRight(),minimumValue(rootNode->getRight()));
        rootNode->setKey(tmp->getKey());
        rootNode->setRight(removeRecursive(rootNode->getRight(),tmp->getKey()));
    }
}

// keep going left until we reach the leftmost node. That node is the smallest value in the tree.
int BinaryTree::minimumValue(Node* rootNode)
{
    int minValue = rootNode->getKey();
    while(rootNode->getLeft() != nullptr)
    {
        minValue = rootNode->getLeft()->getKey();
        rootNode = rootNode->getLeft();
    }
    return minValue;
}

Node* BinaryTree::remove(int key)
{
    return removeRecursive(root,key);
}

void BinaryTree::toStringRecursive(Node* rootNode,int numSpaces,std::vector<std::string> &output)
{
	//base case
    if(rootNode==nullptr)return;
    numSpaces+=7; //increment spaces each level

	// start with right side so that right reads top to bottom. More human reader friendly.
    toStringRecursive(rootNode->getRight(),numSpaces,output);

    // add spaces
	output.push_back("\n");
    for(int i=7;i<numSpaces;i++)
    	output.push_back(" ");

    // add the Node key
    output.push_back(std::to_string(rootNode->getKey()));

    // do left side once right is done, since left will be below right.
    toStringRecursive(rootNode->getLeft(),numSpaces,output);
}

std::string BinaryTree::toString()
{
	std::vector<std::string> output;
	toStringRecursive(root,0,output);
	std::string out;
	for(std::string s : output)
		out+=s;
	return out;
}

int BinaryTree::heightRecursive(Node* rootNode)
{
    if(rootNode==nullptr) return 0;
    return 1+std::max(heightRecursive(rootNode->getLeft()),heightRecursive(rootNode->getRight()));
}

int BinaryTree::height()
{
    return heightRecursive(root);
}
