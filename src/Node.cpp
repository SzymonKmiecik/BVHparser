
#include "Node.h"


void Node::showName()
{
	std::cout << name << std::endl;
}

Node::Node(std::string n)
{
	name = n;
}


Node::~Node()
{
}
