#include <iostream>
#include "GEAH_Compressor.h"
#include "TextCompressor.h"

int main()
{
	TextCompressor compressor;
	compressor.openFile("gnu.txt");
	compressor.compress("compressed.bin");
	compressor.extract("compressed.bin");
	return 0;
}
