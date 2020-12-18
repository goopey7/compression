#include <iostream>
#include "GEAH_Compressor.h"
#include "TextCompressor.h"

int main()
{
	TextCompressor compressor;
	compressor.openFile("geah.txt");
	compressor.compress("compressed.txt");
	compressor.extract("extracted.txt");
	return 0;
}
