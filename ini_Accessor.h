#ifndef ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H

#include <string>


class IniAccessor {
 private:
  std::string filename_;
  std::string user_name_;
  std::string warthunder_client_path_;

 public:
  IniAccessor(const std::string& filename);
  std::string user_name();
  std::string warthunder_client_path();

  void export_ini();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_INIT_READER_H
