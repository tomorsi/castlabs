#include <iostream>

#include "mpegparser.h"
#include "mpegparserexception.h"

using namespace castlabs;

void help(void)
{
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "mpegparser [filename]" << std::endl << std::endl;

}

//
// Bonus Questions:
// 1. The MDAT is xml which tends to consume large amounts of space, the maximum length
// that can be supported with this specification is a 4 bytes unsigned, or 4GB. 
// 2. The code will extract and write to the file system the images, in our example
// there are three. 
// 

int main(int argc, char *argv[])
{
    int exitcode = 0;

    try {

	if (argc<2)
	{
	    help();
	    throw std::invalid_argument("no file specified");
	}
	else
	{
	    std::string filepath = argv[1];

	    MpegParser parser(filepath);
	    parser.Parse();
	}
    } 
    catch (std::exception& e)
    {
	std::cout << "exception: " << std::endl;
	exitcode = -1;
    }
    catch (MpegParserException &e)
    {
	std::cout << e.description() << std::endl;
	exitcode = -2;
    }
    catch (XmlMdatParserException &e)
    {
	std::cout << e.description() << std::endl;
	exitcode = -2;
    }

    return exitcode;
}
