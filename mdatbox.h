#ifndef __MDATBOX__H_
#define __MDATBOX__H_

#include "box.h"

namespace castlabs {

class MdatBox : public Box
{

 private:
  static const char *XMLIMAGEELEMENT;
  static const char *XMLIMAGEIDATTR;
  static const char *XMLIMAGETYPEATTR;
  static const char *XMLIMAGEENCODEDATTR;
  static const char *XMLIMAGEENCODEDATTRVALUE;

 public:
  MdatBox(int length, std::string boxtype, std::ifstream& ifs);

  void writeimagefile(std::string fn, std::string type, std::string data);

  void unmarshal(unsigned char *buffer, int length);

};

}

#endif
