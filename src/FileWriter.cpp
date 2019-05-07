#include "FileWriter.h"

void FileWriter::writeTocsv(std::stringstream stream)
{
	std::ofstream file;
	file.open("try.csv");
	file << stream.rdbuf();
	file.close();
}