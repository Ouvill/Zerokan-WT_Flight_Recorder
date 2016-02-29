#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H

#include <string>
#include <vector>
#include "http_client.h"
#include "picojson.hpp"
#include "damages.h"

class HudmsgConnector {

 private:
  HttpClient *http_;
  int lastEvt_ = 0;
  int lastDmg_ = 0;
  int get_damages_array(std::string json, picojson::array &json_array);


 public:
  HudmsgConnector();
  ~HudmsgConnector();
  int get_damages(Damages& damages);


};

#endif //ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
