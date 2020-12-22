//
// Created by Sam on 17/12/2020.
//

#include "TextCompressor.h"
#include "HuffmanTree.h"
#include <map>

// this is used to swap two elements of our char array when sorting them using bubble sort
void swap(char &a, char &b)
{
	char temp = a;
	a=b;
	b=temp;
}

// I chose bubble sort because I already have a headache and I don't want it to get worse than it already is
void bubbleSortByFrequency(char chars[],std::map<char,uint64_t> &f, int size)
{
	for(int i=0;i<size-1;i++)
	{
		for(int j=0;j<size-i-1;j++)
		{
			if(f[chars[j]] > f[chars[j + 1]])
			{
				swap(chars[j],chars[j + 1]);
			}
		}
	}
}

// traverses huffman tree gathering 1s and 0s until reaching a leaf node
// at which point you can stop and store the sequence of 1s and 0s used to reach the character
// this doesn't actually do the compression, it just creates the mappings
void compressRecursive(Node* root, std::map<char,std::string> &huffCode,const std::string &str)
{
	if(root==nullptr)return;

	// node with no children
	if(root->getLeft()==nullptr&&root->getRight()==nullptr)
		huffCode[root->getChar()]=str;

	compressRecursive(root->getLeft(),huffCode,str+"0");
	compressRecursive(root->getRight(),huffCode,str+"1");
}

void extractRecursive(Node* root, int &index, std::string bits, std::string &out)
{
	if (root == nullptr)return;
	// found a node w/ no children
	if (root->getLeft()==nullptr && root->getRight()==nullptr)
	{
		out+=root->getChar();
		return;
	}
	index++;
	if (bits[index] == '0') // go left if 0, right if 1
		extractRecursive(root->getLeft(), index, bits,out);
	else
		extractRecursive(root->getRight(), index, bits,out);
}

// we can only write one byte at a time, so we need to accumulate a byte before writing our bits
void writeBit(bool bit,int &currentBit, unsigned char &bitBuffer, FILE* fp)
{
	if(bit)bitBuffer |= (1<<currentBit);
	currentBit++;
	if(currentBit==8)
	{
		fwrite(&bitBuffer,1,1,fp);
		currentBit=0;
		bitBuffer=0;
	}
}

// this should be called after a write since we need to ensure our final byte gets written
// so we flood the remaining bits with 0s
int flushBits(int &currentBit, unsigned char &bitBuffer, FILE* fp)
{
	int extraBits=0;
	while (currentBit)
	{
		writeBit(false,currentBit,bitBuffer,fp);
		extraBits++;
	}
	return extraBits;
}

void TextCompressor::compress(std::string fileName)
{
	// create a map to keep track of character frequency
	std::map<char,uint64_t> frequency;
	std::string originalText;
	int numUniqueChars=0;
	for(const std::string &v : *file)
	{
		originalText+=v+'\n';
		for(char c : v)
		{
			frequency[c]++;
			if(frequency[c]==1)
				numUniqueChars++;
		}
		frequency['\n']++;
		if(frequency['\n']==1)numUniqueChars++;
	}
	originalText=originalText.substr(0,originalText.length()-1);
	frequency['\n']--;
	if(frequency['\n']==1)numUniqueChars--;

	// create dynamic ptr of characters in the file
	char* charsSortedByLeastFrequency = new char[numUniqueChars];
	int currentIndex=0;
	for(const std::string &v : *file)
	{
		for(char c : v)
		{
			bool bIsAlreadyInArray=false;
			for(int i=0;i<numUniqueChars;i++)
			{
				char ch = charsSortedByLeastFrequency[i];
				if(ch==c)
				{
					bIsAlreadyInArray=true;
					break;
				}
			}
			if(!bIsAlreadyInArray)
			{
				charsSortedByLeastFrequency[currentIndex]=c;
				currentIndex++;
			}
		}
	}

	// sort the array in order from least frequency to most frequency
	bubbleSortByFrequency(charsSortedByLeastFrequency,frequency, numUniqueChars);

	// construct huffman tree
	HuffmanTree tree(charsSortedByLeastFrequency,numUniqueChars,frequency);

	std::map<char,std::string> huffCode; // map of characters to their binary codes as a string
	compressRecursive(tree.root,huffCode,"");

	std::string str;
	for (char c : originalText)
		str += huffCode[c]; // encode the original string
	int currentBit=0;
	unsigned char bitBuffer;
	FILE* fp = fopen(fileName.c_str(),"w");
	for(char c : str)
		writeBit(std::stoi(std::string(1, c)), currentBit, bitBuffer, fp);
	int extraBits = flushBits(currentBit,bitBuffer,fp);
	fclose(fp);
	tree.saveToFile(extraBits,fileName+".tree");

	// traverse the huffman tree and decode the huffman code
	int index = -1;
	std::string out;
	while (index < (int)str.size() - 2)
	{
		extractRecursive(tree.root, index, str,out);
	}
	std::cout << out;
}

void TextCompressor::extract(std::string fileName)
{
	HuffmanTree tree(fileName+".tree");
	std::ifstream f(fileName, std::ios::binary | std::ios::in);
	std::string bits;
	char c;
	while(f.get(c))
	{
		for(int i=0;i<8;i++)
		{
			bits+=std::to_string(((c >> i) & 1));
		}
	}
	int extraBits = std::stoi(ReadAndWrite::readFile(fileName+".tree.mapping")->at(0));
	bits=bits.substr(0, bits.length() - extraBits); // cut off extra bits

	// traverse the huffman tree and decode the huffman code
	int index = -1;
	std::string out;
	while (index < (int)bits.size() - 2)
	{
		extractRecursive(tree.root, index, bits,out);
	}
	ReadAndWrite::writeFile(out,fileName+".txt");
}
