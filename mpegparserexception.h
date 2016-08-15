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

}
#endif 

