//
// Created by Sam on 17/12/2020.
//

#include "HuffmanTree.h"
#include "ReadAndWrite.h"
#include <queue>
#include <fstream>

// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
class comparator // this is used for our priority queue
		// priority queue is a max heap (highest priority is max value)
		// we are going to make it behave as a min heap using this class
		// which forces our priority queue to behave as a min heap.
{
public:
	// this is how we determine the order
	bool operator() (Node* l, Node* r)
	{
		return l->getKey() > r->getKey();
	}
};

HuffmanTree::HuffmanTree(std::map<char, uint64_t> &frequency)
{
	std::priority_queue<Node*,std::vector<Node*>,comparator> queue;

	// loop through all pairs in the map and create nodes
	for(auto pair : frequency)
	{
		Node* node = new Node(pair.second);
		node->setChar(pair.first);
		queue.push(node);
	}
	// determine children (remember the queue is already sorted)
	while(queue.size()!=1)
	{
		Node* left = queue.top(); // top of the queue
		queue.pop(); // remove from queue
		Node* right = queue.top();
		queue.pop();

		// create new node with the two lowest frequencies
		Node* newNode = new Node(left->getKey()+right->getKey());
		newNode->setChar('\0'); // null char (we only care about the characters in the leaf nodes)
		newNode->setLeft(left);
		newNode->setRight(right);
		queue.push(newNode);
	}
	root=queue.top();
	map = frequency;
}

void saveToFileRecursive(Node* node, FILE* fp)
{
	if(node==nullptr)
	{
		fprintf(fp,"%d'%c'", -1,'\0');
		return;
	} // -1 represents a null node
	else
	{
		fprintf(fp,"%d'%c'",node->getKey(),node->getChar());
		saveToFileRecursive(node->getLeft(),fp);
		saveToFileRecursive(node->getRight(),fp);
	}
}
void HuffmanTree::saveToFile(int extraBits, const std::string& fileName)
{
	FILE *fp = fopen(std::string(fileName).c_str(), "w");
	saveToFileRecursive(root,fp);
	fclose(fp);
	std::string mapping=std::to_string(extraBits)+'\n';
	for(auto pair : map)
	{
		char c=pair.first;
		std::string freq = std::to_string(pair.second);
		mapping+=std::string(1,c).append("|").append(freq).append("\n"); // Delimiter is \n
	}
	ReadAndWrite::writeFile(mapping,fileName+".mapping");
}

void HuffmanTree::readFileRecursive(Node* &node, FILE* fp)
{
	// reconstruct tree
	int num;
	char c;
	if(!fscanf(fp,"%d'%c'",&num,&c)||num==-1)
		return;
	node = new Node(num);
	node->setChar(c);
	readFileRecursive(*node->getLeftDblPtr(),fp);
	readFileRecursive(*node->getRightDblPtr(),fp);
}

HuffmanTree::HuffmanTree(const std::string& fileName)
{
	std::vector<std::string>* mapping = ReadAndWrite::readFile("compressed.txt.tree.mapping");
	for(std::string s : *mapping)
	{
		if(!s.empty())
		{
			char c = s[0];
			if(c=='|')map['\n']=std::stoll(s.substr(s.find('|')+1));
			else
				map[c] =std::stoll(s.substr(s.find('|')+1));
		}
	}
	FILE* fp = fopen(fileName.c_str(), "r");
	root= nullptr;
	readFileRecursive(root,fp);
	fclose(fp);
}
