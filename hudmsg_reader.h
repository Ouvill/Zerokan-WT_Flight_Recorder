#ifndef ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
#define ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H


#include <string>
#include <vector>
#include "http_client.h"
#include "picojson.hpp"


class HudmsgConnector {

 private:
//  HttpClient *http;
  int lastEvt = 0;
  int lastDmg = 0;
  int get_damages_array(std::string json, picojson::array &json_array);


 public:
  HudmsgConnector();
  ~HudmsgConnector();
  int get_damages(picojson::array &damages);


};

class Damage {
 private:
  int id_;
  std::string msg_;
  std::string sender_;
  bool eneny_;
  std::string mode_;

 public:
  Damage(int id, std::string msg, std::string sender, bool enemy, std::string mode);

};

class Damages {
 private:
  std::vector<Damage> damages;
};

class DamageMsg {
 private:
  std::string killer_;
  std::string killer_airframe_;
 public:
  DamageMsg(const std::string& msg);
  std::string killer();
  std::string killer_airframe();
  std::string victim();
};

class ShotDownMsg : public DamageMsg {
 private:
//  std::string killer_;
//  std::string killer_airframe_;
  std::string victim_;
  std::string victim_airframe_;

 public:
  ShotDownMsg(const std::string& msg);
  std::string victim();
  std::string victim_airframe();


};

class DestroyedMsg : public DamageMsg{
 private:
//  std::string killer_;
//  std::string killer_airframe_;
  std::string victim_;

 public:
  DestroyedMsg(const std::string& msg);
  std::string victim();

};


#endif //ZEROKAN_WT_FLIGHT_RECORDER_HUBMSG_READER_H
