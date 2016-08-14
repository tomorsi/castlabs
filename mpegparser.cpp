#include <memory>
#include <fstream>
#include "mpegparser.h"

using namespace castlabs;

// This method cracks out the different Box types, and dispatches
// to specific handlers for derived Box types. In our implementation
// we only have a need to handle the MDAT type and the Container types
// specifically. 
void MpegParser::NextBox(int length, std::string type)
{
    if (type == "mdat")
    {
	MdatBox box(length, type, m_ifstream);
	Handle(box);

    }
    else if (type == "moof" || type == "traf")
    {
	ContainerBox box(length, type, m_ifstream);
	Handle(box);
    }
    else
    {
	// general box handler. 
    }

}

// Overloaded HandleBox method for MDAT that needs to display
// the xml and crack out the u64 encoded images. 
void MpegParser::HandleBox(MdatBox& box)
{
	std::cout << box << std::endl;
}

// Handles the two container Box Type of MOOF and TRAF.
void MpegParser::HandleBox(ContainerBox& box)
{
    int len = box.length();
    while (length > 0)
    {
	int childlen = readlength();
	std::string childtype = readtype();
	NextBox(childen, childtype);
	length -= childen;
    }
}

MpegParser::MpegParser(const std::string& filepath)
    :m_filepath(filepath)
{
    m_ifstream.open(m_filepath, std::ifstream::in|std::ifstream::binary);
    if (!m_ifstream)
    {
	throw std::invalid_argument("couldn't open file: " + m_filepath);
    }

    
} 


  
// Start the parser if a parsing exception occurs
// this method will throw an exception.
void MpegParser::Parse(void)
{
    int length = readlength();
    std::string type = readtype();

    while (m_ifstream.good())
    {
	NextBox(length,type);

	length = readlength();
	type = readtype();
    }
}

int MpegParser::readlength(void)
{
    char lenbuf[4];
    ifs.read(lenbuf,4);
    int length = (lenbuf[0]<<24) | (lenbuf[1]<<16) | 
	(lenbuf[2]<<8) | (lenbuf[3]); 
    return length;
}

std::string MpegParser::readtype(void)
{
    char typebuf[3];
    ifs.read(typebuf,3);
    std::string type = std::string(typebuf,3);
    return type;
}
