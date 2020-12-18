//
// Created by Sam on 17/12/2020.
//

#include "HuffmanTree.h"
#include <queue>

// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
class comparator // this is used for our priority queue
		// priority queue is a max heap (highest priority is max value)
		// we are going to make it behave as a min heap using this class
		// which forces our priority queue to behave as a min heap.
{
public:
	bool operator() (Node* l, Node* r)
	{
		return l->getKey() > r->getKey();
	}
};

HuffmanTree::HuffmanTree(char* sortedChars, int size, std::map<char, uint64_t> &frequency)
{
	std::priority_queue<Node*,std::vector<Node*>,comparator> queue;
	for(auto pair : frequency)
	{
		Node* node = new Node(pair.second);
		node->setChar(pair.first);
		queue.push(node);
	}
	while(queue.size()!=1)
	{
		Node* left = queue.top();
		queue.pop();
		Node* right = queue.top();
		queue.pop();

		// create new node with the two lowest frequencies
		Node* newNode = new Node(left->getKey()+right->getKey());
		newNode->setChar('\0'); // null char
		newNode->setLeft(left);
		newNode->setRight(right);
		queue.push(newNode);
	}
	root=queue.top();
}