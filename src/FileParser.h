#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"

struct KEYWORDS
{
	static const std::string root;
	static const std::string name;

};


class FileParser
{

	void parseRaw(std::string*, std::vector<Node>*);
public:
	FileParser(std::string* , std::vector<Node>*);
	~FileParser();
};


