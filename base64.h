#ifndef __BASE64_H__
#define __BASE64_H__

#include <vector>

namespace castlabs
{

typedef unsigned char BYTE;
std::vector<BYTE> base64_decode(std::string const& encoded_string);

}

#endif
