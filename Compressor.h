//
// Created by Sam on 08/12/2020.
//

#ifndef COMPRESSION_COMPRESSOR_H
#define COMPRESSION_COMPRESSOR_H


#include <string>
#include <utility>
#include <vector>
#include "ReadAndWrite.h"

class Compressor
{

public:
	std::vector<std::string>* file=nullptr;
	std::vector<std::string>* compressedFile=nullptr;

	virtual void openFile(std::string fileName){file=ReadAndWrite::readFile(std::move(fileName));}

	std::string charCount();

	virtual void compress(std::string fileName)=0;
	virtual void extract(std::string fileName)=0;
};


#endif //COMPRESSION_COMPRESSOR_H
