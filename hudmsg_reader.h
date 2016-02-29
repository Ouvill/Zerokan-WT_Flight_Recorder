#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H


#include <string>
#include "http_client.h"
#include "picojson.hpp"


class HudmsgReader{

 private:
//  HttpClient *http;
  int lastEvt = 0;
  int lastDmg = 0;

 public:
  HudmsgReader();
  ~HudmsgReader();
  int get_msg();


  int get_damages_array(std::string json, picojson::array &json_array);
};

class Damage {
 private:
  int id;
  std::string msg;
  std::string sender;
  bool emeny;
  std::string mode;

 public:

};

class ShotDownMsg {
 private:
  std::string killer;
  std::string killer_airframe;
  std::string victim;
  std::string victim_airframe;
};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
