#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "tinyfiledialogs.h" //for cros platform dialog box


class FileReader
{
	std::string filePath;
	

	std::string ChoseFilePath();
	std::string ReadBvhFile();

public:
	FileReader(std::string*);
	~FileReader();


};


