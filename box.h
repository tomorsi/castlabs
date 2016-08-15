
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
  Box(int length, std::string type, std::ifstream& ifs);

  size_t length(void) { return m_length; }

  friend std::ostream& operator<<(std::ostream& ostrm, Box& box);

};


}

#endif
