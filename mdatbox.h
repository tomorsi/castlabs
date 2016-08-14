#ifndef __MDATBOX__H_
#define __MDATBOX__H_

#include "box.h"

namespace castlabs {

  class MdatBox : public Box
{

 public:
  MdatBox(std::ifstream& ifs);

};

}

#endif
