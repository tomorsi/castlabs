#ifndef __MDATBOX__H_
#define __MDATBOX__H_

#include <vector>

#include "base64.h"
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
  
  std::string m_xmldocument;

 public:
  MdatBox(int length, std::string boxtype);

  void writeimagefile(std::string fn, std::string type, std::vector<BYTE>& decoded);

  void unmarshal(unsigned char *buffer, int length);

  friend std::ostream& operator<<(std::ostream& ostrm, MdatBox& box);
};

}

#endif
