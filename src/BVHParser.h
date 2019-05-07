
#include "FileParser.h"
//#include <direct.h>
//#include <sys/stat.h>
//#include <cstdlib>       //for mkdir 

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
	std::string file_path;
	
public:

 BVHParser();
 BVHParser (const std::string*, std::vector<Node>&, std::string&);
 ~BVHParser();

 void CheckTokens(const std::string*);
 //void InputNodeIntoSkeleton(Node*, std::vector<Node>);
 std::stringstream printSkeletonDetails();
 std::string ParseName(std::string);
 float* parseOffset(std::string, float*);
 void calcHierarchyDepth(int, unsigned &);
 std::string parseRawMotionValues(const std::string*);
 std::string ParseChannelsOrder(std::string, Node*);
 unsigned parseFrameCount(std::string);
 float parseFrameTime(std::string);
 Node parseEndSite(std::string);
 int findParentOffset(unsigned, std::vector<Node>&);
 void nodesMotionVectorReserve();
 std::string* trimMotionValues( const std::string*);
 void trim(std::string&, unsigned);
 void parseMotion(const std::string*);
 void writeCsv(std::string, std::string, std::string);
 void trimPath();
 std::stringstream printXYZcoords(Node);
};