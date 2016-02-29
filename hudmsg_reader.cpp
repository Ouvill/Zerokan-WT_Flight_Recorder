#include "hudmsg_reader.h"
#include "picojson.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

HudmsgConnector::HudmsgConnector() {
//  http = new HttpClient("localhost:8111");

}

HudmsgConnector::~HudmsgConnector() {
//  delete http;
}

int HudmsgConnector::get_damages(picojson::array &damages) {

  std::cout << "test" << std::endl;
//  std::string get_string;
//  std::string json;
//  get_string = "/hudmsg?lastEvt" + std::to_string(lastEvt) + "&lastDmg" = std::to_string(lastDmg);
//  http->get_data(get_string, json);

  picojson::value v;
  std::ifstream ifs;

  ifs.open("hudmsg.json");
  std::istreambuf_iterator<char> it(ifs);
  std::istreambuf_iterator<char> last;
  std::string json(it , last);

  ifs.close();

  get_damages_array(json, damages);

  std::stringstream ss;
  std::string dst_msg = "";

  for (picojson::array::iterator i = damages.begin(); i != damages.end(); ++i) {
    picojson::object damage = i->get<picojson::object>();
    Damage(damage["id"].get<double>(), damage["msg"].get<std::string>(),
           damage["sender"].get<std::string>(), damage["enemy"].get<bool>(),
           damage["mode"].get<std::string>());
    lastDmg=damage["id"].get<double>();
  }
}

int HudmsgConnector::get_damages_array(std::string json, picojson::array &damages)
{
  picojson::value v;
  std::string err = parse(v, json);
  if(!err.empty()) {
    std::cerr << picojson::get_last_error() << std::endl;
    return 1;
  }

  picojson::object &o = v.get<picojson::object>();
  damages = o["damage"].get<picojson::array>();

  return 0;
}

//std::string msg の データ
//=ECVAS= DK_DaiZi_CN (スピットファイア F) shot down =BAT= masterchieffffff (ウェリントン)
//Jokebo (IL-10) destroyed 駆逐艦"
Damage::Damage(int id, std::string msg, std::string sender, bool enemy, std::string mode) {
  this->id_ = id;
  this->msg_ = msg;
  this->sender_ = sender;
  this->eneny_ = enemy;
  this->mode_ = mode;

  std::size_t is_shot_down = msg.find(" shot down ");
  std::size_t is_destroy = msg.find(" destroyed ");

  if (is_shot_down != std::string::npos) {
    ShotDownMsg(this->msg_);
  }

  if (is_destroy) {
    DestroyedMsg(this->msg_);
  }
}

ShotDownMsg::ShotDownMsg(const std::string& msg) {
  std::string keyword = " shot down ";
  std::size_t first_open_quote = msg.find("(");
  killer_ = std::string(msg, 0, first_open_quote -1 );
  std::size_t first_close_quote = msg.find(")");
  killer_airframe_ = std::string(msg, first_open_quote + 1,first_close_quote - first_open_quote - 1);

  std::size_t shot_down_pos = msg.find(keyword);
  std::size_t after_keyword_pos = shot_down_pos + keyword.length();

  std::size_t secound_open_quote = msg.find("(", after_keyword_pos);
  victim_ = std::string(msg, after_keyword_pos, secound_open_quote - after_keyword_pos -1) ;
  std::size_t secound_close_quote = msg.find(")", after_keyword_pos);
  victim_airframe_ = std::string(msg, secound_open_quote + 1, secound_close_quote - secound_open_quote -1);

}

std::string ShotDownMsg::killer() {
  return killer_;
}

std::string ShotDownMsg::killer_airframe(){
  return killer_airframe_;
}

std::string ShotDownMsg::victim() {
  return victim_;
}

std::string ShotDownMsg::victim_airframe() {
  return victim_airframe_;
}

//std::string msg のデータ
//Jokebo (IL-10) destroyed 駆逐艦"
DestroyedMsg::DestroyedMsg(const std::string& msg) {
  std::string keyword = " destroyed ";

  std::size_t open_quote_pos = msg.find("(");
  killer_ = std::string(msg, 0, open_quote_pos -1 );


}


