#include "damages.h"
#include <string>


Msg::Msg(std::string msg):std::string(msg) {};

bool Msg::isShotDownMsg() {
  if (find(" shot down ") != std::string::npos) { return true;}
  else {return false;};
}

bool Msg::isDestoryedMsg() {
  if (find(" destroyed ") != std::string::npos ) {
    return true;
  } else { return false;};
}



//std::string msg の データ
//=ECVAS= DK_DaiZi_CN (スピットファイア F) shot down =BAT= masterchieffffff (ウェリントン)
//Jokebo (IL-10) destroyed 駆逐艦"
Damage::Damage(int id, std::string msg, std::string sender, bool enemy, std::string mode) : msg_(msg) {
  this->id_ = id;
  this->sender_ = sender;
  this->eneny_ = enemy;
  this->mode_ = mode;
}

Msg Damage::msg() { return msg_;};

void Damages::serch_shot_down() {

}

DamageMsg::DamageMsg(const std::string& msg) {
  std::size_t open_quote_pos = msg.find("(");
  killer_ = std::string(msg, 0, open_quote_pos -1);
  std::size_t close_quote_pos = msg.find(")");
  killer_airframe_ = std::string(msg, open_quote_pos + 1, close_quote_pos - open_quote_pos -1);
}

std::string DamageMsg::killer() {return killer_;}
std::string DamageMsg::killer_airframe() {return killer_airframe_; }

ShotDownMsg::ShotDownMsg(const std::string& msg) : DamageMsg(msg) {
  std::string keyword = " shot down ";

  std::size_t keyword_pos = msg.find(keyword);
  std::size_t after_keyword_pos = keyword_pos + keyword.length();

  std::size_t secound_open_quote = msg.find("(", after_keyword_pos);
  victim_ = std::string(msg, after_keyword_pos, secound_open_quote - after_keyword_pos -1) ;
  std::size_t secound_close_quote = msg.find(")", after_keyword_pos);
  victim_airframe_ = std::string(msg, secound_open_quote + 1, secound_close_quote - secound_open_quote -1);

}

std::string ShotDownMsg::victim() {
  return victim_;
}

std::string ShotDownMsg::victim_airframe() {
  return victim_airframe_;
}

//std::string msg のデータ
//Jokebo (IL-10) destroyed 駆逐艦"
DestroyedMsg::DestroyedMsg(const std::string& msg) : DamageMsg(msg) {
  std::string keyword = " destroyed ";
  std::size_t keyword_pos = msg.find(keyword);
  std::size_t after_keyword_pos = keyword_pos + keyword.length();
  victim_ = std::string(msg, after_keyword_pos);
}

std::string DestroyedMsg::victim() {
  return victim_;
}
