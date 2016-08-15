#ifndef __MDATBOX__H_
#define __MDATBOX__H_

#include "box.h"

namespace castlabs {

  class MdatBox : public Box
{

 public:
  MdatBox(int length, std::string boxtype, std::ifstream& ifs);

};

}

#endif
