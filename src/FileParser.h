#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"

#define bvh 0x01
#define not_supported 0x02


class FileParser
{
	int data_type;
	void parseRaw(const std::string*); //get data format
public:
	FileParser( const std::string*);
	FileParser();
	int GetDataType();
	virtual ~FileParser();
};


