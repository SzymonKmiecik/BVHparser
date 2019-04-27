#include "BVHParser.h"

	  const std::string KEYWORDS::hierarchy="HIERARCHY";
	  const std::string KEYWORDS::motion="MOTION";
	  const std::string KEYWORDS::root="ROOT";
	  const std::string KEYWORDS::joint="JOINT";
	  const std::string KEYWORDS::offset="OFFSET";
	  const std::string KEYWORDS::channels="CHANNELS";
	
	  const std::string KEYWORDS::end_site="End Site";
	  const std::string KEYWORDS::frames="Frames";
	  const std::string KEYWORDS::frame_time="Frame Time";
	
	  const std::string KEYWORDS::left_bracket="{";
	  const std::string KEYWORDS::right_bracket="}";





BVHParser::BVHParser(const std::string* data, std::vector<Node>& global_skeleton) : skeleton(global_skeleton)
{
	//this->skeleton = global_skeleton;
	skeleton.reserve(100);
	this->raw_data_text = data;
	CheckTokens(raw_data_text);
}

BVHParser::BVHParser() : FileParser()
{
 std::cout << "bvh parser initialized" << std::endl;
}

BVHParser::~BVHParser()
{
	
}

void BVHParser::CheckTokens(const std::string* data)
{
	Node* temp_node_data = new Node;
	std::stringstream stream;
	stream.str(*data);
	std::string tmp;
	unsigned depth = 0;
	while (std::getline(stream, tmp, '\n'))
	{
  		if (tmp.find(KEYWORDS::hierarchy) != std::string::npos) //
		{
		
		//	parseHierarchy();
			//std::stringstream ss(tmp);
			//std::string junkToken;
			//ss >> junkToken >> junkToken;
			//node_data.setOffset( new float[3]{3.0f, 2.1f, 1.2f});
			//skeleton.push_back(Node(junkToken));
		}
		else if (tmp.find(KEYWORDS::root) != std::string::npos) //
		{
			temp_node_data->setName(ParseName(tmp));
		}
		else if (tmp.find(KEYWORDS::motion) != std::string::npos) //
		{
			skeleton.push_back(*temp_node_data);
			parseRawMotionValues(&tmp);
		}
		else if (tmp.find(KEYWORDS::joint) != std::string::npos) //
		{
			skeleton.push_back(*temp_node_data);
			temp_node_data = new Node;
			temp_node_data->setName(ParseName(tmp));
		}
		else if (tmp.find(KEYWORDS::offset) != std::string::npos) //
		{
			float p[3];
			parseOffset(tmp, p);
			temp_node_data->setOffset(p);
		}
		else if (tmp.find(KEYWORDS::channels) != std::string::npos) //
		{
			temp_node_data->setChannelsOrder(ParseChannelsOrder(tmp, temp_node_data));
		}
		else if (tmp.find(KEYWORDS::end_site) != std::string::npos) //
		{
			skeleton.push_back(*temp_node_data);
			temp_node_data = new Node;
			*temp_node_data = parseEndSite(tmp);
		}
		else if (tmp.find(KEYWORDS::frames) != std::string::npos) //
		{
			parseFrameCount(tmp);
		}
		else if (tmp.find(KEYWORDS::frame_time) != std::string::npos) //
		{
			parseFrameTime(tmp);
		}
		else if (tmp.find(KEYWORDS::left_bracket) != std::string::npos) //
		{
			calcHierarchyDepth(+1, depth);
			temp_node_data->setHierarchyDepth(depth);
			unsigned parent_offset = findParentOffset(depth, skeleton);
			temp_node_data->setParentVectorOffset(parent_offset);
		}
		else if (tmp.find(KEYWORDS::right_bracket) != std::string::npos) //
		{
			calcHierarchyDepth(-1, depth);
		}		
	}
	printSkeletonDetails();
}

void BVHParser::printSkeletonDetails()
{
	std::vector<Node>::iterator it;
	bool segmentDef= false;
	for(it = skeleton.begin(); it != skeleton.end(); it++)
	{
		
		for (unsigned i = 0; i <= it->getHierarchyDepth(); i++)
		{ std::cout << "|" ; } 
		{}
		std::cout << "depth:  " << it->getHierarchyDepth() << " ";
		it->showName(); 
		
		if(segmentDef)
		 { std::cout << "  parent: "; skeleton[it->getParentVectorOffset()].showName(); std::cout << std::endl; }
		else
		{ std::cout << std::endl; }
		segmentDef = true;
		
		float* offsets = it->getOffset();
		std::cout << "Offset: "; 
		for(int i=0; i<3; i++)
		{
			std::cout << offsets[i] << " ";
		}
			std::cout << std::endl;
		
	}
}

std::string BVHParser::ParseName(std::string text_line)
{
	std::string name;
	std::stringstream stream;
	stream.str(text_line);
	stream >> name  >> name;
	return name;
}



float* BVHParser::parseOffset(std::string line, float* p)
{
	std::stringstream stream;
	std::string junk;
	stream.str(line);
	stream >> junk  >> p[0] >> p[1] >> p[2];
	return p;
}

void BVHParser::calcHierarchyDepth(int x, unsigned &depth)
{
	 depth += x; 
}

std::string BVHParser::parseRawMotionValues(const std::string*)
{
	return "str";
}

std::string BVHParser::ParseChannelsOrder(std::string line, Node* bone)
{
	std::string channels;
	std::stringstream stream;
	std::string junk;
	stream.str(line);
	stream >> junk;
	int channelCount;
	stream >> channelCount;
	bone->setChannelsCount(channelCount);
	for(int i = 0; i < channelCount; i++)
	{
		stream >> channels[i]; 
		stream >> junk;
	}
	return channels;
}

unsigned BVHParser::parseFrameCount(std::string)
{
	return 6;
}

double BVHParser::parseFrameTime(std::string)
{
	return 0.033;
}

Node BVHParser::parseEndSite(std::string)
{
	return Node("End Site");
}

unsigned BVHParser::findParentOffset(unsigned x,std::vector<Node>& y)
{
	unsigned index = 1;
	//for ( std::vector<Node>::iterator i = y.end(); i-- != y.begin(); index++)
	for (std::vector<Node>::reverse_iterator it = y.rbegin(); it != y.rend(); it++, index++)
	{
		if (it->getHierarchyDepth() == (x-1))
		{ return (y.size()-index); } 
	}
	return 0;
}

