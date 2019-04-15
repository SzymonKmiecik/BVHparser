// BVHReader.cpp : Defines the entry point for the console application.
//

#include "FileReader.h"
#include "FileParser.h"
#include "Node.h"
#include <vector>


int main()
{
    std::string BVHText;
    std::vector< Node >* skeleton = new std::vector< Node >();
    FileReader* reader = new FileReader( &BVHText);
    delete reader;
    reader = NULL;
    FileParser* parser = new FileParser( &BVHText, skeleton);
    delete parser;
    parser = NULL;
    std::cout << "deleted" << std::endl;
    for (Node i : *skeleton)
    {
        i.showName();
    }

    return 0;

}

