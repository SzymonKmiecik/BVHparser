
#include "FileParser.h"

 struct KEYWORDS
{
	 static const std::string hierarchy;
	 static const std::string motion;
	 static const std::string root;
	 static const std::string joint;
	 static const std::string offset;
	 static const std::string channels;
	
	 static const std::string end_site;
	 static const std::string frames;
	 static const std::string frame_time;
	
	 static const std::string left_bracket;
	 static const std::string right_bracket;
};

class BVHParser : public FileParser
{
	std::vector<Node> skeleton;
	const std::string* raw_data_text;
	
public:

 BVHParser();
 BVHParser (const std::string*, std::vector<Node>&);
 ~BVHParser();

 void CheckTokens(const std::string*);
 //void InputNodeIntoSkeleton(Node*, std::vector<Node>);
 void printSkeletonDetails();
 std::string ParseName(std::string);
 float* parseOffset(std::string, float*);
 void calcHierarchyDepth(int, unsigned &);
 std::string parseRawMotionValues(const std::string*);
 std::string ParseChannelsOrder(std::string, Node*);
 unsigned parseFrameCount(std::string);
 double parseFrameTime(std::string);
 Node parseEndSite(std::string);
 unsigned findParentOffset(unsigned, std::vector<Node>&);
};