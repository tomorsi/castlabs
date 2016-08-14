#ifndef __BOX__H_
#define __BOX__H_

#include <string>
#include <fstream>

namespace castlabs {

class Box
{
 protected:
  const std::string m_boxtype;
  size_t m_length;


 public:
  Box(std::ifstream& ifs);

};


}

#endif
