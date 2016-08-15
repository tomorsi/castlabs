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
	std::cout << "MpegParserException: " << std::endl;
	exitcode = -2;
    }

    return exitcode;
}
