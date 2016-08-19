
#include "mpegparserexception.h"

namespace castlabs {

XmlMdatParserException::XmlMdatParserException(const char *description, int row, int column)
    :m_description(description),m_row(row),m_column(column)
{
}

}
