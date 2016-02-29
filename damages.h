#ifndef ZEROKAN_WT_FLIGHT_RECORDER_DAMAGES_H
#define ZEROKAN_WT_FLIGHT_RECORDER_DAMAGES_H

#include <string>
#include <vector>

class Msg : public std::string {
 public:
  Msg(std::string msg);
  bool isShotDownMsg();
  bool isDestoryedMsg();

};

class Damage {
 private:
  int id_;
  Msg msg_;
  std::string sender_;
  bool eneny_;
  std::string mode_;

 public:
  Damage(int id, std::string msg, std::string sender, bool enemy, std::string mode);
  Msg msg();

};

class Damages :public std::vector<Damage>{

 public:
  void serch_shot_down();
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
  std::string victim_;
  std::string victim_airframe_;

 public:
  ShotDownMsg(const std::string& msg);
  std::string victim();
  std::string victim_airframe();


};

class DestroyedMsg : public DamageMsg{
 private:
  std::string victim_;

 public:
  DestroyedMsg(const std::string& msg);
  std::string victim();

};

#endif //ZEROKAN_WT_FLIGHT_RECORDER_DAMAGES_H
