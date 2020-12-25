//
// Created by Sam on 17/12/2020.
//

#ifndef COMPRESSION_HUFFCOMPRESSOR_H
#define COMPRESSION_HUFFCOMPRESSOR_H

#include "Compressor.h"
#include "BinaryTree.h"

class HuffCompressor : public Compressor
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


#endif //COMPRESSION_HUFFCOMPRESSOR_H
