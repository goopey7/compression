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

	map = frequency;
}

void saveToFileRecursive(Node* node, FILE* fp)
{
	if(node==nullptr)
	{
		fprintf(fp,"%d'%c'", -1,'\0');
		return;
	} // * represents a null node
	else
	{
		fprintf(fp,"%d'%c'",node->getKey(),node->getChar());
		saveToFileRecursive(node->getLeft(),fp);
		saveToFileRecursive(node->getRight(),fp);
	}
}
void HuffmanTree::saveToFile(const std::string& fileName)
{
	FILE *fp = fopen("tree.txt", "w");
	saveToFileRecursive(root,fp);
	fclose(fp);
	std::string mapping;
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
}
