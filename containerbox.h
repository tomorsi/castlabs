#ifndef __CONTAINERBOX__H_
#define __CONTAINERBOX__H_

#include "box.h"

namespace castlabs {

class ContainerBox : public Box
{
 public:
  ContainerBox(int length, std::string type);

  void read(std::ifstream& ) {
    // don't actuall read the data for the container, allow the recursion
    // in NextBox to handle this container items. 
  }

};

}

#endif
