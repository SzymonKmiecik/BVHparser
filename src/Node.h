#pragma once
#include <iostream>
#include <string>
#include <sstream>

typedef struct
{
	float x, y, z;
} OFFSET;

class Node
{
	std::string name = "";
	int parent_vector_offset;
	OFFSET offset;
	Node* parent;
	unsigned hierarchy_depth;
	std::string* raw_motion_values;
	std::string channels_order = "";
	unsigned channels_count;
	unsigned *frames_number = nullptr;
	float *frame_time = nullptr;
	//matrix initiators needed

public:
	void setName(std::string);
	void setParent(Node*);
	void setOffset(float*);
	void setHierarchyDepth(unsigned);
	void setRawMotionValues(std::string);
	void setChannelsOrder(const std::string);
	void setParentVectorOffset(unsigned);
	void setChannelsCount(unsigned);
	void setFramesNumberPtr(unsigned);
	void setFrameTime(float);
	void setParentPtr(Node*);
	
	unsigned getParentVectorOffset();
	std::stringstream showName();
	float* getOffset();
	unsigned getHierarchyDepth();
	void printParentName();
	void printChannelsOrder();
	void printFramesNumber();
	void printFrameTime();
	
	
	Node();
	Node(std::string);
	~Node();

};

