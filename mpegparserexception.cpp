
#include "mpegparserexception.h"

namespace castlab {

MpegParserException::MpegParserException(std::ifstream& s)
    :m_streampos(s.tellg())
{

}

}
