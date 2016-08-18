
#include <iostream>
#include <locale>
#include <fstream>

#include "tinyxml.h"
#include "mdatbox.h"
#include "mpegparserexception.h"

namespace castlabs {

// This should really be built into std::string.
static std::string tolower(std::string s)
{
    std::transform(s.end(),s.begin(),s.end(),::tolower);
    return s;
}

MdatBox::MdatBox(int length, std::string type, std::ifstream& ifs)
    :Box(length, type, ifs)
{
}

void MdatBox::writeimagefile(std::string fn, std::string type, std::string data)
{
    std::ofstream ofs(fn);
    ofs.open(fn);
    if (!ofs.is_open())
    {
	throw std::invalid_argument("couldn't open file: " + fn);
    }
    ofs << data;
    ofs.close();
}

// We employ tinyxml which is basically 4 source files and
// two headers to parse the xml portion of the mdat box, we
// choose tinyxml instead of the built in STL with regexp
// matcher because parsing attributes are necessary for the
// filename, file type, and encoding. 
void MdatBox::unmarshal(unsigned char *buffer, int length)
{
    std::cout << "Enter: MdatBox::unmarshal" << std::endl;

    TiXmlDocument document;
    
    std::string parseable((char*)buffer,length);

    document.Parse(parseable.c_str());

    if (document.Error())
    {
	throw XmlMdatParserException(document.ErrorDesc(),document.ErrorRow(),document.ErrorCol());
    }

    // Document is a Node but not a element so its impracticle
    // to use the NoChildren method, because I need Elements 
    // int he for-loop.
    TiXmlElement *element = document.FirstChildElement();
    while (element)
    {
	if (element->ValueStr() == XMLIMAGEELEMENT)
	    break;
	element = element->FirstChildElement();
    }

    // Found images. 
    while (element)
    {
	std::string fn;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGEIDATTR, &fn))
	{ 
	}
	std::string type;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGETYPEATTR, &type))
	{
	}
	std::string encoding;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGEENCODEDATTR, &encoding))
	{
	    std::locale loc;
	    // if we are not base64 encoded skip this image, probably should log. 
	    if (tolower(encoding) == XMLIMAGEENCODEDATTRVALUE)
	    {
		std::string text = element->GetText();
		writeimagefile(fn, type, text);
	    }
	    else
	    {
		// log a warning and go on to the next possible image. 
	    }
	}
	element = element->NextSiblingElement(XMLIMAGEELEMENT);
    }
}

const char *MdatBox::XMLIMAGEELEMENT = "smpte:image";
const char *MdatBox::XMLIMAGEIDATTR = "xml:id";
const char *MdatBox::XMLIMAGETYPEATTR = "xml:imagetype";
const char *MdatBox::XMLIMAGEENCODEDATTR = "xml:encoding";
const char *MdatBox::XMLIMAGEENCODEDATTRVALUE = "base64";
}
