
#include "mpegparserexception.h"

namespace castlab {

MpegParserException::MpegParserException(istream& s)
    :m_streampos(s.tellg())
{

}

}
