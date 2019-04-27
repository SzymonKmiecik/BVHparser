
#include "Node.h"


void Node::showName()
{
	std::cout << name;
}

Node::Node()
{
	
}

Node::Node(std::string n)
{
	name = n;
}

Node::~Node()
{
}


void Node::setName(std::string x)
{
	this->name = x;
}

void Node::setParent(Node* x)
{
 //this->parent = x;
}

void Node::setOffset(float* x)
{
	this->offset.x = x[0];
	this->offset.y = x[1];
	this->offset.z = x[2];
}

float* Node::getOffset()
{
	float* data = new float(3);
	data[0] = this->offset.x;
	data[1] = this->offset.y;
	data[2] = this->offset.z;
	return data;
}

unsigned Node::getHierarchyDepth()
{
	return this->hierarchy_depth;
}

void Node::setHierarchyDepth(unsigned x)
{
	this->hierarchy_depth = x;
}

void Node::getParentName()
{
//	this->parent->showName();
}

unsigned Node::getParentVectorOffset()
{
	return this->parent_vector_offset;
}

void Node::setParentVectorOffset(unsigned x)
{
	this->parent_vector_offset = x;
}

void Node::setChannelsOrder(std::string x)
{
	this->channels_order = x;
}

void Node::setChannelsCount(unsigned x)
{
	this->channels_count = x;
}
//void Node::setParent(Node* n)
//{
//this->parent = n;
//}
