//
// Created by Sam on 17/12/2020.
//

#ifndef COMPRESSION_TEXTCOMPRESSOR_H
#define COMPRESSION_TEXTCOMPRESSOR_H

#include "Compressor.h"
#include "BinaryTree.h"

class TextCompressor : public Compressor
{
	BinaryTree* root;
	std::string nameOfFile;
public:
	void openFile(std::string fileName) override
	{
		Compressor::openFile(fileName);
		nameOfFile=fileName;
	}
	void compress(std::string fileName) override;
	void extract(std::string fileName) override;
};


#endif //COMPRESSION_TEXTCOMPRESSOR_H
