
#include "FileParser.h"

const std::string bvh_type = "HIERARCHY";


FileParser::FileParser()
{

}

FileParser::FileParser( const std::string* n)
{
	parseRaw(n);
}

FileParser::~FileParser() = default;

void FileParser::parseRaw( const std::string* data)
{
	std::stringstream stream;
	stream.str(*data);
	std::string tmp;
	while (std::getline(stream, tmp, '\n'))
	{
		if (tmp.find(bvh_type) != std::string::npos)
		{	
			this->data_type = bvh;
			break; 
		}
		else
		{
			this->data_type = not_supported;
		}
	}
	std::cout << "Type checked" << std::endl;
}



int FileParser::GetDataType()
{
	return this->data_type;
}
