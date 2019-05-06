
#include "Node.h"


std::stringstream Node::showName()
{
	std::stringstream buffer;
	buffer << name << std::endl; 
	return buffer;
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
	delete frame_time;
	delete frames_number;
}


void Node::setName(std::string x)
{
	this->name = x;
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

//void Node::getParentName()
//{
//	this->parent->showName();
//}

unsigned Node::getParentVectorOffset()
{
	return this->parent_vector_offset;
}

void Node::setParentVectorOffset(unsigned x)
{
	this->parent_vector_offset = x;
}

void Node::setChannelsOrder(const std::string x)
{
	this->channels_order = x;
}

void Node::setChannelsCount(unsigned x)
{
	this->channels_count = x;
}

void Node::setFramesNumberPtr(unsigned x)
{
this->frames_number = new unsigned {x};
}

void Node::printChannelsOrder()
{
 std::cout << "CHANNELS:" << this->channels_count << " ORDER:" << this->channels_order << " "; 
}

unsigned Node::printFramesNumber()
{
//std::cout << "FRAMES:" << *this->frames_number << " ";
return *this->frames_number;
}

void Node::setParentPtr(Node* x)
{
this->parent = x;
//this->frames_number = setRootFramesPointers();
//this->frames_number = parent->frames_number;
}

void Node::printParentName()
{
 std::cout << "PARENT: ";
 parent->showName();
}

void Node::printFrameTime()
{
std::cout << "FRAME TIME:" << *this->frame_time;
}

void Node::setFrameTime(float x)
{ 
this->frame_time = new float {x};
}

unsigned* Node::setRootFramesPointers()
{
	if (parent != nullptr)
		{ return parent->setRootFramesPointers(); }
	else  
		{ return frames_number; }
}

void Node::reserveMatrixVector(unsigned frames)
{
this->local_transform.reserve(frames);
this->global_transform.reserve(frames);
this->xyz_pos.reserve(frames);
for (unsigned i=0; i < xyz_pos.size(); i++)
	xyz_pos[i].reserve(3);
}

unsigned Node::getChannelsNumber()
{
return this->channels_count;
}

std::vector<double> Node::composeMatrixTransform(unsigned channels, std::string motion_value)
{
	std::vector<double> values;
	values.reserve(channels);
	size_t last_pos = 0;
	size_t curr_pos = 0;
	double temp;
	for (unsigned i =0; i< channels; i++)
	{
		curr_pos = motion_value.find(' ', last_pos+1);
		std::stringstream buffer;
		std::string t_str = motion_value.substr(last_pos, curr_pos - last_pos);
		buffer.str(t_str);
		last_pos = curr_pos;
		
		buffer >> temp;
		values.push_back(temp);
	}
	if(this->channels_order =="XYZZXY")
	{
		Matrix<double> temp_transform(4,4,0.0);
		temp_transform.singular();
		//Matrix<double> lol(1,1,1);
		temp_transform.input_offset(new double[3]{this->offset.x+values[0],this->offset.y+values[1], this->offset.z+values[2]});
		temp_transform.rotZ(values[3]);
		temp_transform.rotX(values[4]);
		temp_transform.rotY(values[5]);
		this->local_transform.push_back(temp_transform);
		this->global_transform.push_back(this->composeGlobalTransform());
		//this->origin = computeOrigin(); calculating origin is correct, but test shows that origin must be 0,0,0
		this->origin.resize(4,0.0);
		this->origin[3] = 1.0;
		this->xyz_pos.push_back(computeXYZcords());
	}
	else if(this->channels_order =="XYZZYX")
	{
		
	}
	else if(this->channels_order =="XYZXZY")
	{
		
	}
	else if(this->channels_order =="XYZXYZ")
	{
		
	}
	else if(this->channels_order =="XYZYXZ")
	{
		
	}
	else if(this->channels_order =="XYZYZX")
	{
		
	}
	//rest of channels order will commmign soon
	return values;
}

Matrix<double> Node::composeGlobalTransform()
{
	if(parent == nullptr)
		return local_transform.back();
	else
	{
		return(this->parent->composeGlobalTransform()*this->local_transform.back());
		//return (this->local_transform.back()*this->parent->composeGlobalTransform());
	}
}

std::vector<double> Node::computeOrigin()
{
	std::vector<double> origin;
	origin.resize(4,0.0);
	if(parent == nullptr)
	{
		origin[0]+= this->offset.x;
		origin[1]+= this->offset.y;
		origin[2]+= this->offset.z;
		origin[3]= 1.0;
		return origin;
	}
	else
	{
		//sumation for multiple values for recurrency
		std::transform(origin.begin(),origin.end(),parent->computeOrigin().begin(),origin.begin(), std::plus<double>());
		return origin;
	}
}

std::vector<double> Node::computeXYZcords()
{
	return this->global_transform.back()*this->origin;
	//return this->origin*this->global_transform.back();
}


//void Node::setParent(Node* n)
//{
//this->parent = n;
//}
