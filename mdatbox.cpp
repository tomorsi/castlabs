
#include "tinyxml.h"
#include "mdatbox.h"
#include "mpegparserexception.h"

namespace castlabs {

MdatBox::MdatBox(int length, std::string type, std::ifstream& ifs)
    :Box(length, type, ifs)
{
}

// We employ tinyxml which is basically 4 source files and
// two headers to parse the xml portion of the mdat box, we
// choose tinyxml instead of the built in STL with regexp
// matcher because parsing attributes are necessary for the
// filename, file type, and encoding. 
void MdatBox::unmarshal(unsigned char *buffer, int length)
{
    TiXmlDocument document;
    
    std::string parseable((char*)buffer,length);

    document.Parse(parseable.c_str());

    if (document.Error())
    {
	throw XmlMdatParserException(document.ErrorDesc(),document.ErrorRow(),document.ErrorCol());
    }

    for (auto node = document.FirstChild("smpte:image"); node ; node = document.NextSibling("smpte:image"))
    {

    }
}

}
