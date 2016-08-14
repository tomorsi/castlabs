
#include <memory>
#include <fstream>
#include "mpegparser.h"

uses castlabs;

// This method cracks out the different Box types, and dispatches
// to specific handlers for derived Box types. In our implementation
// we only have a need to handle the MDAT type and the Container types
// specifically. 
std::shared_ptr<Box> void MpegParser::CrackBox(std::string type)
{
    if (type == "mdat")
    {
	return new std::shared_ptr<MdatBox>(m_ifstream);
    }
    else if (type == "moof" || type == "traf")
    {
	return new std::shared_ptr<ContainerBox>(m_ifstream);
    }
    else
    {
	// general box handler. 
    }

}

// Overloaded HandleBox method for MDAT that needs to display
// the xml and crack out the u64 encoded images. 
void MpegParser::HandleBox(std::shared_ptr<MdatBox> mdatbox)
{

}

// Handles the two container Box Type of MOOF and TRAF.
void MpegParser::HandleBox(std::shared_ptr<ContainerBox> containerbox)
{

}

MpegParser::MpegParser(const std::string& filepath)
    :m_filepath(filepath)
{
    m_ifstream.open(m_filepath, std::ifstrean::in||std::ifstream::binary);
    if (!m_ifstream)
    {
	throw std::invalid_argument("couldn't open file: " + m_filepath);
    }

    
} 
  
// Start the parser if a parsing exception occurs
// this method will throw an exception.
void MpegParser::Parse(void);
{

    char buffer[4];
    m_ifstream.read(buffer,sizeof(buffer));

    while (m_ifstream.good())
    {
	std::string type(buffer);
	std::shared_ptr<Box> box = std::crackbox(type);
	HandleBox(box);
	m_ifstream.read(buffer,sizeof(buffer));
    }
	
}
