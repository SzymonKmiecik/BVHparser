
#include "FileParser.h"

const std::string KEYWORDS::root = "ROOT";
const std::string KEYWORDS::name = "JOINT";



FileParser::FileParser(std::string* n, std::vector<Node>* skeleton)
{
	parseRaw(n, skeleton);
}

FileParser::~FileParser()
{
}

void FileParser::parseRaw(std::string* data, std::vector<Node>* skeleton)
{
	std::stringstream stream;
	stream.str(*data);
	std::string tmp;
	while (std::getline(stream, tmp, '\n'))
	{
  		if (tmp.find(KEYWORDS::name) != std::string::npos) //
		{
			std::stringstream ss(tmp);
			std::string junkToken;
			ss >> junkToken >> junkToken;
			skeleton->push_back(Node(junkToken));
		}
	}
	std::cout << "parsed!" << std::endl;
}
