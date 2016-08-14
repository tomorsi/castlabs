#ifndef __CONTAINERBOX__H_
#define __CONTAINERBOX__H_

#include "box.h"

namespace castlabs {

class ContainerBox : public Box
{
 public:
  ContainerBox(std::ifstream& ifs);

};

}

#endif
