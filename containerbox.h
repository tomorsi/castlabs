#ifndef __CONTAINERBOX__H_
#define __CONTAINERBOX__H_

namespace castlabs {

class ContainerBox : public Box
{
 public:
  ContainerBox(std::string type, ifstream& ifs);

};

}
