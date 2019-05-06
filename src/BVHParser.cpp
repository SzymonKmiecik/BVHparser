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
	unsigned current_line = 0; //for debug
	bool only_motion_left = false;
	if (only_motion_left) {}; //unused defender
//try{
	while (std::getline(stream, tmp, '\n'))
	{	
	current_line++;	
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
			std::string order = ParseChannelsOrder(tmp, temp_node_data);
			std::string sub_order = order.substr(1,6);//remove first junk character from parsing loop
			temp_node_data->setChannelsOrder(sub_order);
		//	temp_node_data->setChannelsOrder(ParseChannelsOrder(tmp, temp_node_data));
		}
		else if (tmp.find(KEYWORDS::end_site) != std::string::npos) //
		{
			skeleton.push_back(*temp_node_data);
			temp_node_data = new Node;
			*temp_node_data = parseEndSite(tmp);
		}
		else if (tmp.find(KEYWORDS::frames) != std::string::npos) //
		{
			skeleton[0].setFramesNumberPtr( parseFrameCount(tmp));
		}
		else if (tmp.find(KEYWORDS::frame_time) != std::string::npos) //
		{
			skeleton[0].setFrameTime(parseFrameTime(tmp));
			only_motion_left = true;
		}
		else if (tmp.find(KEYWORDS::left_bracket) != std::string::npos) //
		{
			calcHierarchyDepth(+1, depth);
			temp_node_data->setHierarchyDepth(depth);
			int parent_offset = findParentOffset(depth, skeleton);
			temp_node_data->setParentVectorOffset(parent_offset);
			if (parent_offset > -1)
			{
			temp_node_data->setParentPtr(&skeleton[parent_offset]);
			}
		}
	
		else if (tmp.find(KEYWORDS::right_bracket) != std::string::npos) //
		{
			calcHierarchyDepth(-1, depth);
		}
		if (only_motion_left)
		break;
	 }
	const std::string* motion_raw_text = trimMotionValues(raw_data_text);
	nodesMotionVectorReserve();
//	std::cout << *motion_raw_text << std::endl;
	parseMotion(motion_raw_text);
	printSkeletonDetails();
//}
//		catch(unsigned e)
//		{
//		std::cout << "Parse error at line: " << e << std::endl; 
//		}
}


void BVHParser::parseMotion(const std::string* data)
{
	std::stringstream stream;
	stream.str(*data);
	std::string tmp;
	std::vector<Node>::iterator it;
	while (std::getline(stream, tmp, '\n'))
	{
		//unsigned node_motion_offset =0;
		std::vector<std::vector<double>> test;
		for(it = skeleton.begin(); it != skeleton.end(); it++)
		{
			std::string temp = it->showName().str();
			std::string check = "End Site";
		if (temp.find(KEYWORDS::end_site) == std::string::npos)
		{
			test.push_back(it->composeMatrixTransform(it->getChannelsNumber(), tmp));
			trim(tmp, it->getChannelsNumber()); // remove used motion values
		}
		else 
			continue;
		}
		//for(unsigned i=0; i<test.size();i++)
		//{
		//std::cout << std::endl;
		//for(unsigned j=0; j<test[i].size(); j++);
		//		std::cout << test[i][j] << " ";
		//}
		//getchar();
//		std::cout << "Vector test size: " <<test.size() << std::endl;
	}
}


 std::string* BVHParser::trimMotionValues(const std::string* data)
{
	std::string* motion_values = new std::string;
	*motion_values = *data;
	size_t motion_pos = data->find("Frame Time:");
	size_t forward_pos = data->find("\n", motion_pos);
	//size_t reverse_pos = data.rfind("\n", motion_pos);
	//*motion_values = data->erase(0, forward_pos);
	motion_values->erase(0,forward_pos+1);
	return motion_values;
}

void BVHParser::nodesMotionVectorReserve()
{
	std::vector<Node>::iterator it;
	for(it = skeleton.begin(); it != skeleton.end(); it++)
	{
	it->reserveMatrixVector(skeleton[0].printFramesNumber());	
	}
}

void BVHParser::printSkeletonDetails()
{
	std::vector<Node>::iterator it;
	bool segmentDef= false;
	for(it = skeleton.begin(); it != skeleton.end(); it++)
	{
		
		for (unsigned i = 0; i <= it->getHierarchyDepth(); i++)
		{ std::cout << "" ; } 
		{}
		std::string name_buffer_end_site_check = it->showName().str(); 
		std::cout << "DEPTH:" << it->getHierarchyDepth() << " NAME:" << name_buffer_end_site_check;
		
		if(segmentDef)
		 { 
			 //std::cout << "  parent: "; skeleton[it->getParentVectorOffset()].showName(); std::cout << std::endl; }
			it->printParentName();
		 }
		else
		{
			std::cout << "FRAMES:" <<	it->printFramesNumber() << " ";
			it->printFrameTime();
		}
		std::cout << std::endl; 
		segmentDef = true;
		
		float* offsets = it->getOffset();
		std::cout << "OFFSET: "; 
		for(int i=0; i<3; i++)
		{
			std::cout << offsets[i] << " ";
		}
			std::cout << "\n";
			if (name_buffer_end_site_check.find(KEYWORDS::end_site) == std::string::npos)
			it->printChannelsOrder();

			std::cout << std::endl ;
	}
				std::cout << "Skeleton size: " << skeleton.size() << " Nodes\n";
				
				//skeleton[0].local_transform[0].print_data();
				//skeleton[0].global_transform[1].print_data();
				//skeleton[2].local_transform[2].print_data();
				//skeleton[2].global_transform[2].print_data();
				for(unsigned i = 0; i < skeleton[2].xyz_pos.size(); i++)
				{
					std::cout << std::endl;
					for(unsigned j = 0; j < skeleton[2].xyz_pos[i].size()-1; j++)
					{ std::cout << skeleton[2].xyz_pos[i][j] << " "; }
					
				}
				std::cout << "\nDisplayed position X Y Z for LeftLeg node (test)\n" << std::endl;
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
	junk = stream.str();
	//channels += junk[0];
	for(unsigned i = 1; i < junk.size()-1; i++)
	{
		if(junk[i] == ' ' && junk[i-1]!=' ') {channels+=junk[i+1];} //getting first letters of channels i.e "XYZYXZ"
		//stream >> channels[i]; 
		//stream >> junk;
	}
//bone->setChannelsOrder(channels);
	return channels;
}

unsigned BVHParser::parseFrameCount(std::string line)
{
	unsigned frames;
	std::string junk;
	std::stringstream stream;
	stream.str(line);
	stream >> junk;
	stream >> frames;
	return frames;
}

float BVHParser::parseFrameTime(std::string line)
{
	float frame_time;
	std::string junk;
	std::stringstream stream;
	stream.str(line);
	stream >> junk >> junk;
	stream >> frame_time;
	return frame_time;
}

Node BVHParser::parseEndSite(std::string)
{
	return Node("End Site");
}

int BVHParser::findParentOffset(unsigned x,std::vector<Node>& y)
{
	unsigned index = 1;
	//for ( std::vector<Node>::iterator i = y.end(); i-- != y.begin(); index++)
	for (std::vector<Node>::reverse_iterator it = y.rbegin(); it != y.rend(); it++, index++)
	{
		if (it->getHierarchyDepth() == (x-1))
		{ return (y.size()-index); } 
	}
	return -1;
}

void BVHParser::trim(std::string& x, unsigned rm_count)
{
	size_t pos = 0;
	for (unsigned i =0; i < rm_count; i++)
	{
		pos = x.find(' ',pos+1);
	}
	x.erase(0, pos+1);
	}

