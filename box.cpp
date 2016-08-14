
#include "box.h"

use castlabs;

Box::Box(std::string type, ifstream& ifs)
    : m_boxtype(type)
{
    unsigned char s[3];
    ifstream.read(s,3);
    m_length = (s[0]<<16) | (s[1]<<8) | s[2]; 
}


