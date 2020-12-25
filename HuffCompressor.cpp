//
// Created by Sam on 17/12/2020.
//

#include "HuffCompressor.h"
#include "HuffmanTree.h"
#include <map>
#include <bitset>

// This is how I ended up managing to successfully read and write bits without any odd errors
// https://www.cplusplus.com/forum/general/119145/

// http://en.cppreference.com/w/cpp/language/type_alias
using byte = unsigned char;

// http://en.cppreference.com/w/cpp/types/numeric_limits
constexpr std::size_t BITS_PER_BYTE = std::numeric_limits<byte>::digits;

// http://en.cppreference.com/w/cpp/utility/bitset
using bitsInByte = std::bitset<BITS_PER_BYTE>;

// Reads the binary of a file and returns the 1s and 0s in a string
std::string readBits(const char* fileName)
{
	std::string bitStr;
	std::ifstream file(fileName, std::ios::binary); // open in binary mode
	char c;
	while (file.get(c)) // read byte
		bitStr += bitsInByte(byte(c)).to_string(); // append 1s and 0s to string
	return bitStr;
}

// given a string of 1s and 0s, writes the bits to a file and returns the amount of 0s it padded at the end
int writeBits(std::string bitString, const char* fileName)
{
	int extraBits = 0;

	// Add 0s to the end until the string can be divided into bytes without any remainders
	while (bitString.size() % BITS_PER_BYTE)
	{
		bitString += '0';
		extraBits++;
	}

	std::ofstream file(fileName, std::ios::binary); // open in binary mode

	for (std::size_t i = 0; i < bitString.size(); i += BITS_PER_BYTE)
	{
		// convert each sequence of '0' or '1' to a byte
		byte b = bitsInByte(bitString.substr(i, BITS_PER_BYTE)).to_ulong();
		file << b; // write
	}
	return extraBits;
}

// this is used to swap two elements of our char array when sorting them using bubble sort
void swap(char &a, char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

// I chose bubble sort because I already have a headache and I don't want it to get worse than it already is
void bubbleSortByFrequency(char chars[], std::map<char, uint64_t> &f, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (f[chars[j]] > f[chars[j + 1]])
			{
				swap(chars[j], chars[j + 1]);
			}
		}
	}
}

// traverses huffman tree gathering 1s and 0s until reaching a leaf node
// at which point you can stop and store the sequence of 1s and 0s used to reach the character
// this doesn't actually do the compression, it just creates the mappings
void compressionMapping(Node* root, std::map<char, std::string> &huffCode, const std::string &str)
{
	if (root == nullptr)return;

	// node with no children
	if (root->getLeft() == nullptr && root->getRight() == nullptr)
		huffCode[root->getChar()] = str;

	compressionMapping(root->getLeft(), huffCode, str + "0");
	compressionMapping(root->getRight(), huffCode, str + "1");
}

// traverses the huffman tree by following the 1s and 0s until we reach a leaf node
// At the leaf node we grab the character and append it to our string
void extractRecursive(Node* root, int &index, std::string bits, std::string &out)
{
	if (root == nullptr)return;

	// found a node w/ no children
	if (root->getLeft() == nullptr && root->getRight() == nullptr)
	{
		out += root->getChar();
		return;
	}
	index++;
	if (bits[index] == '0') // go left if 0, right if 1
		extractRecursive(root->getLeft(), index, bits, out);
	else
		extractRecursive(root->getRight(), index, bits, out);
}

// this function is public
void HuffCompressor::compress(std::string fileName)
{
	// create a map to keep track of character frequency
	std::map<char, uint64_t> frequency;
	std::string originalText;
	for (const std::string &v : *file)
	{
		originalText += v + '\n';
		for (char c : v)
			frequency[c]++;
		frequency['\n']++;
	}

	// construct huffman tree
	HuffmanTree tree(frequency);

	// create a map of characters to their binary codes as a string
	std::map<char, std::string> huffCode;
	compressionMapping(tree.root, huffCode, "");

	// using our new map, encode each character of the original text given
	std::string bits;
	for (char c : originalText) // loop through every character and encode using our map
		bits += huffCode[c]; // encode the original string
	int extraBits = writeBits(bits, fileName.c_str()); // we must keep track of spare bits to maintain integrity
	tree.saveToFile(extraBits, fileName + ".tree");
}

void HuffCompressor::extract(std::string fileName)
{
	// reconstruct the huffman tree from the file
	HuffmanTree tree(nameOfFile + ".tree");
	// grab the amount of extra bits to watch out for at the end from the first line of the mapping file
	int extraBits = std::stoi(ReadAndWrite::readFile(nameOfFile + ".tree.mapping")->at(0));
	std::string bits = readBits(nameOfFile.c_str()); // read in the 1s and 0s as string
	bits = bits.substr(0, bits.length() - extraBits); // cut off the extra 0s added to the end

	// traverse the huffman tree and decode the huffman encoded string
	int index = -1;
	std::string out;
	while (index < (int) bits.size() - 2)
		extractRecursive(tree.root, index, bits, out);

	// out is the extracted plaintext, so just write that to a file
	ReadAndWrite::writeFile(out, fileName);
}
