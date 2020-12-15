//
// Created by Sam on 08/12/2020.
//

#ifndef COMPRESSION_GEAH_COMPRESSOR_H
#define COMPRESSION_GEAH_COMPRESSOR_H

#include "Compressor.h"

class GEAH_Compressor : public Compressor
{
public:
	// checks validity of .txt file. Contents are copied from google doc including newline at the end
	bool isValid();

	void compress(std::string fileName) override;
	void extract(std::string fileName) override;
};


#endif //COMPRESSION_GEAH_COMPRESSOR_H
