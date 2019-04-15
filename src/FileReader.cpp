
#include "FileReader.h"


FileReader::FileReader(std::string* RawTextMemory)
{
while (filePath.empty())
{
	filePath =  ChoseFilePath();
}
	//if (filePath != nullptr)
	{
	std::cout << filePath << std::endl;
	*RawTextMemory = ReadBvhFile();
	}
}


FileReader::~FileReader()
{
}

std::string FileReader::ChoseFilePath()
{
	char const* lTheOpenFileName;
	std::string path;
	char const* lFilterPatterns[1] = {"*.bvh"};

	//tinyfd_verbose = -1;
	tinyfd_silent = 1;
try
{
	lTheOpenFileName = tinyfd_openFileDialog(
		"Read bvh",
		"",
		2,
		lFilterPatterns,
		NULL,
		0);
    if (lTheOpenFileName == NULL)
	{
        throw 1;
		return std::string();
	}
	else 
	{
	path = lTheOpenFileName;
	//std::cout << path << std::endl;
	return path;
	}
}
    
catch(int i)
	{
		tinyfd_messageBox(
			"Error",
			"Open file name is NULL",
			"ok",
			"error",
            1);
	}
return path;
}

	//char buffer[MAX_PATH] = "";
	//std::string path = "";
	//OPENFILENAMEA ofn = { 0 };
	//ofn.lStructSize = sizeof(ofn);
	//ofn.lpstrFilter = "BVH Files\0*.bvh\0";
	//ofn.nFilterIndex = 1;
	//ofn.Flags = OFN_FILEMUSTEXIST;
	//ofn.lpstrFile = buffer;
	//ofn.nMaxFile = MAX_PATH;
	//if (!GetOpenFileNameA(&ofn))
	//{
	//	path = "CANCEL";
	//}
	//else
	//{
	//	path = buffer;
	//}
	//return path;


std::string FileReader::ReadBvhFile()
{
	std::ifstream in(filePath);
	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string rawBVH(buffer.str());
	return rawBVH;
}
