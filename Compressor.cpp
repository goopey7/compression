//
// Created by Sam on 08/12/2020.
//

#include "Compressor.h"

std::string Compressor::charCount()
{
	int fileCount=0;
	for(int i=0;i<file->size();i++)
	{
		for(int j=0; j<file->at(i).length();j++)
		{
			fileCount++;
		}
	}
	int compressedCount=0;
	for(int i=0;i<compressedFile->size();i++)
	{
		for(int j=0; j<compressedFile->at(i).length();j++)
		{
			compressedCount++;
		}
	}
	return std::to_string(compressedCount) + "/" + std::to_string(fileCount);
}
