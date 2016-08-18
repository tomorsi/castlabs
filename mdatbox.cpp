
#include <iostream>

#include "tinyxml.h"
#include "mdatbox.h"
#include "mpegparserexception.h"

namespace castlabs {

MdatBox::MdatBox(int length, std::string type, std::ifstream& ifs)
    :Box(length, type, ifs)
{
}

void MdatBox::writeimagefile(std::string fn, std::string type, std::string data)
{

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
    TiXmlElement *elment = document.FirstChildElement();
    while (element)
    {
	if (element.ValueStr() == XMLIMAGEELEMENT)
	    break;
	elment = elment.FirstChildElement();
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
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGEENCODEATTR, &encoding))
	{
	    // if we are not base64 encoded skip this image, probably should log. 
	    if (std::tolower(encoding) == XMLENCODEDATTRVALUE)
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

const std::string MdatBox::XMLIMAGEELEMNT = "smpte:image";
const std::string MdatBox::XMLIMAGEIDATTR = "xml:id";
const std::string MdatBox::XMLIMAGETYPEATTR = "xml:imagetype";
const std::string MdatBox::XMLENCODEDATTR = "xml:encoding";
const std::string MdatBox::XMLENCODEDATTRVALUE = "base64";
}
