#include <iostream>
#include "GEAH_Compressor.h"

int main()
{
	GEAH_Compressor geahCompressor;
	geahCompressor.openFile("geah.txt");
	std::cout << geahCompressor.isValid() << std::endl;
	geahCompressor.compress("compressed.txt");
	std::cout << "Compression rate:" << geahCompressor.charCount() << std::endl;
	return 0;
}
