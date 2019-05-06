#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Matrix.h"

typedef struct
{
	float x, y, z;
} OFFSET;

class Node
{
	std::string name = "";
	int parent_vector_offset;
	OFFSET offset;
	Node* parent = nullptr;
	unsigned hierarchy_depth;
	std::string* raw_motion_values;
	std::string channels_order = "";
	unsigned channels_count;
	unsigned *frames_number = nullptr;
	float *frame_time = nullptr;
	//matrix initiators needed

	unsigned* setRootFramesPointers();


public:
	std::vector<Matrix<double>> local_transform;
	std::vector<Matrix<double>> global_transform;
	std::vector<double> origin;
	std::vector<std::vector<double>> xyz_pos;
 	
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
	void reserveMatrixVector(unsigned);
	
	std::vector<double> composeMatrixTransform(unsigned, std::string);
	Matrix<double> composeGlobalTransform();
	std::vector<double> computeOrigin();
	std::vector<double> computeXYZcords();

	unsigned getParentVectorOffset();
	std::stringstream showName();
	float* getOffset();
	unsigned getHierarchyDepth();
	void printParentName();
	void printChannelsOrder();
	unsigned getChannelsNumber();
	unsigned printFramesNumber();
	void printFrameTime();
	
	
	Node();
	Node(std::string);
	~Node();

};

