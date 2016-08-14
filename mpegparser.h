#ifndef __MPEG_PARSER_H__
#define __MPEG_PARSER_H__

namespace castlabs {


class MpegParser
{

 private:
  const std::string& m_filepath;

  std::unique_ptr<ifstream> m_ifstream;

  // This method cracks out the different Box types, and dispatches
  // to specific handlers for derived Box types. In our implementation
  // we only have a need to handle the MDAT type and the Container types
  // specifically. 
  std::shared_ptr<Box> void HandleBox(std::string type);

  // Overloaded HandleBox method for MDAT that needs to display
  // the xml and crack out the u64 encoded images. 
  void HandleBox(std::shared_ptr<MdatBox> mdatbox);

  // Handles the two container Box Type of MOOF and TRAF.
  void HandleBox(std::shared_ptr<ContainerBox> containerbox);


 public:
  MpegParser(const std::string& filepath); 
  
  // Start the parser if a parsing exception occurs
  // this method will throw an exception.
  void Parse(void);
};

}
