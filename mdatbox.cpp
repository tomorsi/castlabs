
#include "mdatbox.h"

namespace castlabs {

MdatBox::MdatBox(int length, std::string type, std::ifstream& ifs)
    :Box(length, type, ifs)
{
}

}

