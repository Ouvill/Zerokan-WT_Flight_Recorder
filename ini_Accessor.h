#ifndef ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H

#include <string>


class IniReader {
 private:
  std::string user_name_;
  std::string warthunder_client_path_;

 public:
  IniReader(std::string filename);
  std::string user_name();
  std::string warthunder_client_path();



};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H
