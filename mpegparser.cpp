#include <memory>
#include <fstream>
#include <iostream>

#include "mpegparser.h"

using namespace castlabs;

MpegParser::MpegParser(const std::string& filepath)
    :m_filepath(filepath)
{
    m_ifstream.open(m_filepath, std::ifstream::in);
    if (!m_ifstream)
    {
	throw std::invalid_argument("couldn't open file: " + m_filepath);
    }
} 
  

// This method cracks out the different Box types, and dispatches
// to specific handlers for derived Box types. In our implementation
// we only have a need to handle the MDAT type and the Container types
// specifically. 
void MpegParser::NextBox(int length, std::string type)
{
    std::cout << "length: " << length << " type: " << type << std::endl;

    if (type == "mdat")
    {
	MdatBox box(length, type, m_ifstream);
	HandleBox(box);

    }
    else if (type == "moof" || type == "traf")
    {
	ContainerBox box(length, type, m_ifstream);
	HandleBox(box);
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
    while (len > 0)
    {
	int childlen = readlength();
	std::string childtype = readtype();
	NextBox(childlen, childtype);
	len -= childlen;
    }
}

// Start the parser if a parsing exception occurs
// this method will throw an exception.
void MpegParser::Parse(void)
{
    std::cout << "parse" << std::endl;

    int length = readlength();
    std::string type = readtype();

    while (m_ifstream.good())
    {
	std::cout << "reading next" << std::endl;
	NextBox(length,type);

	length = readlength();
	type = readtype();
    }
}

int MpegParser::readlength(void)
{
    unsigned char lenbuf[4];
    m_ifstream.read((char*)lenbuf,4);
    int length = (lenbuf[0]<<24) | (lenbuf[1]<<16) | 
    	(lenbuf[2]<<8) | (lenbuf[3]); 
    //unsigned int *length = (unsigned int*)lenbuf;
    std::cout << "readlength: " << length << std::endl;
    std::cout << std::hex << (int)lenbuf[0] << ":" 
	      << std::hex << (int)lenbuf[1] << ":" 
	      << std::hex << (int)lenbuf[2] << ":" 
	      << std::hex <<(int)lenbuf[3] << std::endl;

    return length;
}

std::string MpegParser::readtype(void)
{
    char typebuf[4];
    m_ifstream.read(typebuf,4);
    std::string type = std::string(typebuf,4);
    return type;
}
