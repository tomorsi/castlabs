
#include <iostream>
#include <iterator>
#include <locale>
#include <fstream>

#include "tinyxml.h"
#include "mdatbox.h"
#include "mpegparserexception.h"

namespace castlabs {

// This should really be built into std::string.
static std::string tolower(std::string s)
{
    std::transform(s.begin(),s.end(),s.begin(),::tolower);
    return s;
}

static TiXmlElement* FindElement(std::string name, TiXmlElement* cur)
{
    TiXmlElement *result = nullptr;

    std::cout << "current element: " << cur->Value() << std::endl;
    
    
    if (cur->ValueStr()==name)
	return cur;


    for (auto next = cur->FirstChildElement(); next ; next = next->NextSiblingElement())
    {
	result = FindElement(name,next);
	if (result)
	    return result;
    }
	
    return result;
}

MdatBox::MdatBox(int length, std::string type, std::ifstream& ifs)
    :Box(length, type, ifs)
{
}

void MdatBox::writeimagefile(std::string fn, std::string type, std::vector<BYTE>& decoded)
{
    std::ofstream ofs(tolower(fn)+"."+tolower(type), std::ios_base::binary);
    if (!ofs.is_open())
    {
	throw std::invalid_argument("couldn't open file: " + fn);
    }

    std::copy(decoded.begin(),decoded.end(), std::ostream_iterator<BYTE>(ofs));

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

    document.Parse(parseable.c_str(),0,TIXML_ENCODING_UTF8);

    if (document.Error())
    {
	throw XmlMdatParserException(document.ErrorDesc(),document.ErrorRow(),document.ErrorCol());
    }

    TiXmlElement *element = FindElement(XMLIMAGEELEMENT, document.RootElement());

    // Found images. 
    while (element)
    {
	std::cout << "element: " << element->Value() << std::endl;

	std::string fn;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGEIDATTR, &fn))
	{ 
	    throw XmlMdatParserException("image attribute not found", element->Row(), element->Column());
	}
	std::string type;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGETYPEATTR, &type))
	{
	    throw XmlMdatParserException("image type attribute not found", element->Row(), element->Column());
	}
	std::string encoding;
	if (TIXML_SUCCESS != element->QueryStringAttribute(XMLIMAGEENCODEDATTR, &encoding))
	{
	    throw XmlMdatParserException("encoding attribute not found", element->Row(), element->Column());
	}

	// if we are not base64 encoded skip this image, probably should log. 
	if (tolower(encoding) == XMLIMAGEENCODEDATTRVALUE)
	{
	    std::string text = element->GetText();
	    std::vector<BYTE>  encoded = base64_decode(text);
	    writeimagefile(fn, type, encoded);
	}
	else
	{
	    throw XmlMdatParserException("image encoding is not base64", element->Row(), element->Column());
	}
    	element = element->NextSiblingElement(XMLIMAGEELEMENT);
    }
}

const char *MdatBox::XMLIMAGEELEMENT = "smpte:image";
const char *MdatBox::XMLIMAGEIDATTR = "xml:id";
const char *MdatBox::XMLIMAGETYPEATTR = "imagetype";
const char *MdatBox::XMLIMAGEENCODEDATTR = "encoding";
const char *MdatBox::XMLIMAGEENCODEDATTRVALUE = "base64";
}
