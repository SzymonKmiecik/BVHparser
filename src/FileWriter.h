#include <fstream>
#include <sstream>
//#include ""

class FileWriter
{	
public:
	FileWriter(std::stringstream x) { }
	~FileWriter() {}
	void writeTocsv(std::stringstream);
private:

};