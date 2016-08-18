
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

void Box::read(std::ifstream& ifs)
{
    std::unique_ptr<unsigned char> buffer(new unsigned char[m_length]);

    ifs.read((char*)buffer.get(),m_length);

    unmarshal(buffer.get(), m_length);
}

void Box::unmarshal(unsigned char* buffer, int length)
{
}


}
