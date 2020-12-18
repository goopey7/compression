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

void compressRecursive(Node* root, std::map<char,std::string> &huffCode,std::string str)
{
	if(root==nullptr)return;

	// node with no children
	if(root->getLeft()==nullptr&&root->getRight()==nullptr)
		huffCode[root->getChar()]=str;

	compressRecursive(root->getLeft(),huffCode,str+"0");
	compressRecursive(root->getRight(),huffCode,str+"1");
}

void decode(Node* root, int &index, std::string str)
{
	if (root == nullptr)
	{
		return;
	}

	// found a node w/ no children
	if (root->getLeft()==nullptr && root->getRight()==nullptr)
	{
		std::cout << root->getChar();
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->getLeft(), index, str);
	else
		decode(root->getRight(), index, str);
}

//TODO write huffman tree to file
//TODO instead of writing binary as string, see if you can actually write the binary so we get a smaller file!
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
		if(frequency['\n']==1)
			numUniqueChars++;
	}
	originalText=originalText.substr(0,originalText.length()-1);
	frequency['\n']--;
	if(frequency['\n']==1)
		numUniqueChars--;

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
	{
		str += huffCode[c];
	}
	ReadAndWrite::writeFile(str,fileName);
	std::string mapping;
	std::string s;
	for(int i=0;i<numUniqueChars;i++)
	{
		char c = charsSortedByLeastFrequency[i];
		 s = std::string(1,c);
		mapping+=  s + "*" + huffCode[charsSortedByLeastFrequency[i]]+'\n';
	}
	ReadAndWrite::writeFile(mapping,fileName+".mapping");

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	std::cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(tree.root, index, str);
	}
}

void TextCompressor::extract(std::string fileName)
{
	std::vector<std::string> v = *ReadAndWrite::readFile(nameOfFile+".mapping");
	std::map<std::string,char> m;
	for(auto & i : v)
	{
		m[i.substr(2)]=i[0];
	}

}
