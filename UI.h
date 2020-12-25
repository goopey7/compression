//
// Created by Sam on 24/12/2020.
//

#ifndef COMPRESSION_UI_H
#define COMPRESSION_UI_H

#include <filesystem>
#include "ReadAndWrite.h"
#include "HuffCompressor.h"
#include "GEAH_Compressor.h"

using namespace std;

void pressEnterToContinue()
{
	std::string s;
	do
	{
		cout << "Press ENTER to continue" << endl;
		ReadAndWrite::getInputAsString(s);
	} while (!s.empty());
}

long getFileSize(const std::string &fileName)
{
	FILE* filePtr = fopen(fileName.c_str(), "rb");
	fseek(filePtr, 0, SEEK_END);
	long size = ftell(filePtr);
	fclose(filePtr);
	return size;
}

void geahMenu()
{
	bool b;
	do
	{
		b=false;
		CLEAR_SCREEN
		cout << "Make sure that the .txt file is named geah.txt and is located in the same directory as the program"
			 << endl;
		pressEnterToContinue();
		ifstream f("geah.txt");
		if (!f.good())
			b=true;

	}
	while(b);


	std::string choice;
	do
	{
		CLEAR_SCREEN
		cout << "===========GREEN EGGS AND HAM===========" << endl;
		cout << "What would you like to do?" << endl;
		cout << "(1) Compress" << endl;
		cout << "(2) Extract" << endl;
		cout << "(0) Exit to Main Menu" << endl;
		ReadAndWrite::getInputAsString(choice);
		if (choice == "1")
		{
			GEAH_Compressor compressor;
			compressor.openFile("geah.txt");
			compressor.compress("geah.geahzip");

			// Calculate Compression Rate
			long compressedSize = getFileSize("geah.geahzip");
			long ogSize = getFileSize("geah.txt");
			cout << "Compression Rate (lower is better): " << ((double) compressedSize) / ((double) ogSize) * 100.0
				 << "%" << endl;
			cout << "Compressed file saved to geah.geahzip" << endl;
			pressEnterToContinue();
		} else if (choice == "2")
		{
			GEAH_Compressor compressor;
			compressor.openFile("geah.geahzip");
			compressor.extract("geah.txt");
			cout << "Extracted file saved to geah.txt" << endl;
			pressEnterToContinue();
		}
	} while (choice != "0");
}

void huffCompressMenu()
{
	std::string fileName;
	bool b;
	do
	{
		CLEAR_SCREEN
		try
		{
			cout << "Please enter the full name of the file you'd like to compress:" << endl;
			ReadAndWrite::getInputAsString(fileName);
			if (fileName.length() > 4)
			{
				b = fileName[fileName.size() - 1] != 't' || fileName[fileName.size() - 2] != 'x' ||
					fileName[fileName.size() - 3] != 't' || fileName[fileName.size() - 4] != '.';
			} else b = true;
		}
		catch (...)
		{
			b = true;
		}
		if (b)
		{
			cout << "File has to be a plaintext file (.txt)" << endl;
			pressEnterToContinue();
		} else
		{
			ifstream f(fileName.c_str());
			if (!f.good())
			{
				b = true;
				cout << "Invalid file/File not found" << endl;
				pressEnterToContinue();
			}
		}

	} while (b);
	HuffCompressor compressor;
	compressor.openFile(fileName);
	std::string compressedFileName = fileName.substr(0, fileName.find_first_of('.')) + ".samzip";
	compressor.compress(compressedFileName);

	// compress produces three files, so let's put them into one file

	// read the binary from the .samzip file
	streampos fileSize;
	ifstream file(compressedFileName, ios::binary);

	file.seekg(0, ios::end);
	fileSize = file.tellg();
	file.seekg(0, ios::beg);

	std::vector<unsigned char> fileData(fileSize);
	file.read((char*) &fileData[0], fileSize);
	std::string binaryStr;
	for (auto c : fileData)
		binaryStr += c;

	// read the .tree file
	std::string tree;
	char c;
	fstream treeIn(compressedFileName + ".tree", fstream::in);
	while (treeIn >> noskipws >> c)
		tree += c;
	binaryStr += "\n**TREE**\n" + tree; // add to the end of the binary file

	// read the .tree.mapping file
	std::string mapping;
	fstream mapIn(compressedFileName + ".tree.mapping", fstream::in);
	while (mapIn >> noskipws >> c)
		mapping += c;
	binaryStr += "\n**MAPPING**\n" + mapping; // add to the end of the binary file

	// write the contents of all 3 files to the .samzip file
	ReadAndWrite::writeFile(binaryStr, compressedFileName);
	cout << "Compressed file saved as " << compressedFileName << endl;

	// Calculate Compression Rate
	long compressedSize = getFileSize(compressedFileName);
	long ogSize = getFileSize(fileName);
	cout << "Compression Rate (lower is better): " << ((double) compressedSize) / ((double) ogSize) * 100.0 << "%"
		 << endl;

	// delete remaining files
	mapIn.close();
	treeIn.close();
	remove(std::string(compressedFileName + ".tree").c_str());
	remove(std::string(compressedFileName + ".tree.mapping").c_str());
	pressEnterToContinue();
}

void huffExtractMenu()
{
	std::string fileName;
	bool b;
	do
	{
		b = false;
		CLEAR_SCREEN
		cout << "Please enter the full name of the samzip you'd like to extract:" << endl;
		ReadAndWrite::getInputAsString(fileName);
		if (fileName.find(".samzip") != fileName.size() - 7)
		{
			b = true;
			cout << "You can only extract files ending in .samzip" << endl;
			pressEnterToContinue();
		} else
		{
			ifstream f(fileName.c_str());
			if (!f.good())
			{
				b = true;
				cout << "Invalid file/File not found" << endl;
				pressEnterToContinue();
			}
		}
	} while (b);

	// we need to break up the .samzip into three files

	// read the entire file using binary
	streampos fileSize;
	ifstream file(fileName, ios::binary);

	file.seekg(0, ios::end);
	fileSize = file.tellg();
	file.seekg(0, ios::beg);

	std::vector<unsigned char> fileData(fileSize);
	file.read((char*) &fileData[0], fileSize);
	std::string binaryStr;
	for (auto c : fileData)
		binaryStr += c;
	file.close();

	// parse out the tree part and store it in a string
	std::string tree = binaryStr.substr(binaryStr.find("\n**TREE**\n") + 10);
	tree = tree.substr(0, tree.find("\n**MAPPING**\n"));
	// parse out the map part and store it in a string
	std::string mapping = binaryStr.substr(binaryStr.find("\n**MAPPING**\n") + 13);
	// cut off tree and mapping from binary
	binaryStr = binaryStr.substr(0, binaryStr.find("\n**TREE**\n"));

	// write the three files
	ReadAndWrite::writeFile(binaryStr, fileName);
	ReadAndWrite::writeFile(tree, fileName + ".tree");
	ReadAndWrite::writeFile(mapping, fileName + ".tree.mapping");

	// send them to our compressor class for extraction
	HuffCompressor compressor;
	compressor.openFile(fileName);
	compressor.extract(fileName.substr(0, fileName.find_last_of(".samzip") - 6) + ".txt");

	// delete all samzip related files
	remove(std::string(fileName + ".tree.mapping").c_str());
	remove(std::string(fileName + ".tree").c_str());
	remove(std::string(fileName).c_str());

	cout << "Extracted file saved as " << fileName.substr(0, fileName.find_last_of(".samzip") - 6) + ".txt" << endl;
	pressEnterToContinue();
}

void huffMenu()
{
	std::string choice;
	do
	{
		CLEAR_SCREEN
		cout << "===========Huffman Encoding===========" << endl;
		cout << "What would you like to do?" << endl;
		cout << "(1) Compress" << endl;
		cout << "(2) Extract" << endl;
		cout << "(0) Exit to Main Menu" << endl;
		ReadAndWrite::getInputAsString(choice);
		if (choice == "1")huffCompressMenu();
		else if (choice == "2")huffExtractMenu();
	} while (choice != "0");
}

void benchmark()
{
	bool b;
	do
	{
		b=false;
		CLEAR_SCREEN
		cout << "Make sure that the .txt file is named geah.txt and is located in the same directory as the program"
			 << endl;
		pressEnterToContinue();
		ifstream f("geah.txt");
		if (!f.good())
			b=true;

	}
	while(b);

	cout << "Lower is better" << endl;

	cout << "Compression rate using GEAH: ";
	GEAH_Compressor geah;
	geah.openFile("geah.txt");
	geah.compress("geah.geahzip");
	double geahRate = (double) getFileSize("geah.geahzip") / (double) getFileSize("geah.txt") * 100;
	cout << geahRate << "%" << endl;

	cout << "Compressing using Huffman encoding (samzip): ";
	HuffCompressor huff;
	huff.openFile("geah.txt");
	huff.compress("geah.samzip");
	double huffRate = (double) (getFileSize("geah.samzip") +
								getFileSize("geah.samzip.tree")
								+ getFileSize("geah.samzip.tree.mapping")) /
					  (double) getFileSize("geah.txt") * 100;
	remove("geah.samzip.tree");
	remove("geah.samzip.tree.mapping");
	cout << huffRate << "%" << endl;
	pressEnterToContinue();
}

void mainMenu()
{
	std::string choice;
	do
	{
		CLEAR_SCREEN
		cout << "**********************************************************" << endl;
		cout << "********************** compression ***********************" << endl;
		cout << "********************** Sam Collier ***********************" << endl;
		cout << "**********************************************************" << endl;
		cout << "Choose which compression algo you'd like to try:" << endl;
		cout << "(1) Universal (Huffman Encoding)" << endl;
		cout << "(2) Green Eggs And Ham (Only works on geah.txt)" << endl;
		cout << "(3) Huffman vs. Green eggs and ham" << endl;
		cout << "(0) Exit Program" << endl;
		ReadAndWrite::getInputAsString(choice);
		if (choice == "1")huffMenu();
		else if (choice == "2")geahMenu();
		else if (choice == "3")benchmark();
	} while (choice != "0");
}

#endif //COMPRESSION_UI_H
