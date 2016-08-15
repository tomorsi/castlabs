
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
  // The size of the type and length in the 
  // file this need is dependent on the file structure. 
  static const int HEADERLENGTH = 8;

  Box(int length, std::string type, std::ifstream& ifs);

  void read(std::ifstream& ifs);

  virtual void unmarshal(unsigned char *buffer);

  size_t length(void) { return m_length; }

  friend std::ostream& operator<<(std::ostream& ostrm, Box& box);

};


}

#endif
