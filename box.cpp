
#include "box.h"

namespace castlabs {

std::ostream& operator<<(std::ostream& ostrm, Box& box)
{


    return ostrm;
}

Box::Box(int length, std::string type)
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
