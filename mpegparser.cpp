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
    std::cout  << "[box] " ;
    std::cout  << "type: " << type ;
    std::cout  << " length: " << length << std::endl;

    if (type == "mdat")
    {
	MdatBox box(length, type);
	box.read(m_ifstream);
	HandleBox(box);

    }
    else if (type == "moof" || type == "traf")
    {
	ContainerBox box(length, type);
	box.read(m_ifstream);
	HandleBox(box);
    }
    else
    {
	m_ifstream.seekg(length,std::ios_base::cur);
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
	if (childlen < 0)
	    break;

	std::string childtype = readtype();

	NextBox(childlen, childtype);
	len = len - Box::HEADERLENGTH - childlen;

    }

}

// Start the parser if a parsing exception occurs
// this method will throw an exception.
void MpegParser::Parse(void)
{
    int length = readlength();
    if (length < 0 ) 
	return;

    std::string type = readtype();

    while (length > 0)
    {
	NextBox(length,type);

	length = readlength();

	if (length <= 0)
	    break;

	type = readtype();
    }
}

int MpegParser::readlength(void)
{
    int curpos = m_ifstream.tellg();

    unsigned char lenbuf[4];
    m_ifstream.read((char*)lenbuf,4);
    int length = (lenbuf[0]<<24) | (lenbuf[1]<<16) | 
    	(lenbuf[2]<<8) | (lenbuf[3]); 

    if (m_ifstream.eof() || !m_ifstream)
	return -1;

    return length - Box::HEADERLENGTH;
}

std::string MpegParser::readtype(void)
{
    char typebuf[4];
    m_ifstream.read(typebuf,4);
    std::string type = std::string(typebuf,4);
    return type;
}
