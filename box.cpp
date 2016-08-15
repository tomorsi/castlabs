
#include "box.h"

namespace castlabs {

std::ostream& operator<<(std::ostream& ostrm, Box& box)
{
    ostrm << std::endl;
    ostrm << "[" << "Box" << "]" << std::endl;
    ostrm << "length: " << box.m_length << std::endl;
    ostrm << "type: " << box.m_boxtype << std::endl;

    return ostrm;
}

Box::Box(int length, std::string type, std::ifstream& ifs)
    :m_length(length),m_boxtype(type)
{
}

}


