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
	int parent_vector_offset;
	OFFSET offset;
	unsigned hierarchy_depth;
	std::string* raw_motion_values;
	std::string channels_order;
	unsigned channels_count;
	//matrix initiators needed

public:
	void setName(std::string);
	void setParent(Node*);
	void setOffset(float*);
	void setHierarchyDepth(unsigned);
	void setRawMotionValues(std::string);
	void setChannelsOrder(std::string);
	void setParentVectorOffset(unsigned);
	void setChannelsCount(unsigned);
	
	unsigned getParentVectorOffset();
	void showName();
	float* getOffset();
	unsigned getHierarchyDepth();
	void getParentName();
	
	
	Node();
	Node(std::string);
	~Node();

};

