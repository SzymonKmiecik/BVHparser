#pragma once
#include <iostream>
#include <string>

typedef struct
{
	float x, y, z;
} OFFSET;

class Node
{
	std::string name = "";
	Node* parent = NULL;
	OFFSET offset;

public:
	void showName();
	Node(std::string);
	~Node();

};

