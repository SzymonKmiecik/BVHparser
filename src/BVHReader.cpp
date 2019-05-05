// BVHReader.cpp : Defines the entry point for the console application.
//

#include "FileReader.h"
#include "FileParser.h"
#include "BVHParser.h"
#include "Node.h"
#include <vector>

void start();

int main()
{

	start();
}

void start()
{
	    std::string BVHText;
    //std::vector< Node > skeleton = new std::vector< Node >();
	std::vector<Node> skeleton;
    FileReader* reader = new FileReader( &BVHText);
    delete reader;
    FileParser* PrimaryParser = new FileParser( &BVHText);
	BVHParser* bvhParser ;
	if (PrimaryParser->GetDataType() == bvh)
	{
		PrimaryParser = new BVHParser( &BVHText, skeleton);
		bvhParser = dynamic_cast<BVHParser*>(PrimaryParser); //for testing
		if (!bvhParser)
			{ std::cout << "Parser cast fault" << std::endl ;}
		if (!PrimaryParser)
			{ std::cout << "Primary parser is also null" << std::endl; }
	}
	else
	{
			std::cout << "data format not supported" << std::endl;
    }
	delete PrimaryParser;
    std::cout << "deleted" << std::endl;
}