#ifndef __MPEG_PARSER_EXCEPTION__
#define __MPEG_PARSER_EXCEPTION__

#include <fstream>
#include <sstream>

namespace castlabs {

class XmlMdatParserException
{
 protected:
  const std::string m_description;
  int m_row;
  int m_column;

 public:
  XmlMdatParserException(const char *description, int row, int column);

  std::string description() {
    std::ostringstream s;
    s << "xml mdata parser exception[" << m_description << "] row: " << m_row << " column: " << m_column;
    return s.str();
  }

};

}
#endif 

