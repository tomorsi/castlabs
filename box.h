#ifndef __BOX__H_
#define __BOX__H_

namespace castlabs {

class Box
{
 protected:
  const std::string m_boxtype;
  size_t m_length;


 public:
  Box(std::string type, ifstream& ifs);

};


}
