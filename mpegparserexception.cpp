
#include "mpegparserexception.h"

namespace castlabs {

MpegParserException::MpegParserException(std::ifstream& s)
    :m_streampos(s.tellg())
{

}

}
