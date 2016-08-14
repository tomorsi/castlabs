#ifndef __MPEG_PARSER_EXCEPTION__
#define __MPEG_PARSER_EXCEPTION__

namespace castlab {

// The base class exception only tracks
// the position in the stream that was 
// unable to be parsed. 
class MpegParserException
{
 protected:
  const streampos &m_streampos;

 public:
  MpegParserException(istream& s);
};

}
#endif 

