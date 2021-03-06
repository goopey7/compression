//
// Created by sam on 21/10/2020.
//
#include "ReadAndWrite.h"

void ReadAndWrite::getInputAsString(std::string& input)
{
    std::getline(std::cin, input);
}

std::string ReadAndWrite::readFileAsString(std::string inFileName)
{
	std::ifstream inFile(inFileName);
	std::string str;
	while(std::getline(inFile,str))
		str+='\n';
	return str;
}

std::vector<std::string>* ReadAndWrite::readFile(std::string inFileName)
{
    // read into our database line by line
    auto* lines=new std::vector<std::string>;
    std::ifstream inFile(inFileName);
    std::string line;
    while(std::getline(inFile,line))
        lines->push_back(line);
    return lines;
}

void ReadAndWrite::writeFile(std::vector<std::string>* outFileContents, const std::string& outFileName)
{
    remove(outFileName.c_str());
    std::string outString;
    for(int i=0;i<outFileContents->size();i++)
    {
        outString+=outFileContents->at(i);
        if(outFileContents->size()>1&&i<outFileContents->size()-1)outString+="\n";
    }
    std::fstream outFile;
    outFile.open(outFileName,std::ios::out | std::ios::trunc);
    outFile << outString;
    outFile.close();
}

void ReadAndWrite::writeFile(const std::string& outFileContents, const std::string& outFileName)
{
	remove(outFileName.c_str());
	std::ofstream outFile(outFileName,std::ios::binary);
	outFile << outFileContents;
	outFile.close();
}
