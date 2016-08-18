
#include "mpegparserexception.h"

namespace castlabs {

MpegParserException::MpegParserException(std::ifstream& s)
    :m_streampos(s.tellg())
{

}

XmlMdatParserException::XmlMdatParserException(const char *description, int row, int column)
    :m_description(description),m_row(row),m_column(column)
{

}

}
