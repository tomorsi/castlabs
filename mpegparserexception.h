#ifndef __MPEG_PARSER_EXCEPTION__
#define __MPEG_PARSER_EXCEPTION__

#include <fstream>

namespace castlabs {

// The base class exception only tracks
// the position in the stream that was 
// unable to be parsed. 
class MpegParserException
{
 protected:
  const std::streampos m_streampos;

 public:
  MpegParserException(std::ifstream& s);
};

class XmlMdatParserException
{
 protected:
  const std::string m_description;
  int m_row;
  int m_column;

 public:
  XmlMdatParserException(const char *description, int row, int column);

};

}
#endif 

