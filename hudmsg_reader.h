#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H

#include <string>
#include <vector>
#include "picojson.hpp"
#include "damages.h"

class HudmsgReader {

 private:
  int lastEvt_ = 0;
  int lastDmg_ = 0;
  int get_damages_array(std::string json, picojson::array &json_array);

 public:
  static const int ERROR_CODE = -1;

  HudmsgReader();
  ~HudmsgReader();
  bool get_damages(Damages& damages);




};

#endif //ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
