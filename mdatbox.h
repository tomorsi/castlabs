#ifndef __MDATBOX__H_
#define __MDATBOX__H_

#include "box.h"

namespace castlabs {

class MdatBox : public Box
{

 private:
  const static std::string XMLIMAGEELEMNT;
  const static std::string XMLIMAGEFILENAMEATTR;
  const static std::string XMLIMAGETYPEATTR;
  const static std::string XMLIMAGEENCODEDATTR;
  const static std::string XMLIMAGEENCODEDATTRVALUE;

 public:
  MdatBox(int length, std::string boxtype, std::ifstream& ifs);

  void writeimagefile(std::string fn, std::string type, std::string data);

  void unmarshal(unsigned char *buffer, int length);

};

}

#endif
