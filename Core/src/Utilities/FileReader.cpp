#include "FileReader.h"
#include <fstream>
#include <iostream>

std::string FileReader::ReadFile(_STRING_CR_ address)
{
	std::string strFile;
	std::fstream file(address);
	char readChar;
	if (!file.is_open())
	{
        file.open("../" + address);
        if(!file.is_open())
        {
            std::cout << "[Error] Can't open file: " + address << std::endl;
        }
	}

	while ((readChar = file.get()) != EOF)
	{
		strFile += readChar;
	}
	file.close();
	return strFile;
}